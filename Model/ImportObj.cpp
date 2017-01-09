#include "ImportObj.h"

ImportObj::ImportObj(char* filename)
{
	FILE* fp;
	fp=fopen(filename,"r");
	if (fp==NULL) return;

    int vn=0;
	char buf[128];
	while(fscanf(fp, "%s", buf) != EOF) 
	{
		switch(buf[0]) 
		{
			float v1,v2,v3;
		case '#':               /* comment */
			/* eat up rest of line */
			fgets(buf, sizeof(buf), fp);
			break;
		case 'v':/* v, vn, vt */
			{	
				switch(buf[1]) 
				{
				case '\0':          /* vertex */
					
					fscanf(fp,"%f %f %f",&v1,&v2,&v3);
					VERTEX vtemp;
					vtemp.xyz[0]=v1;
					vtemp.xyz[1]=v2;
					vtemp.xyz[2]=v3;
					vertex_list.push_back(vtemp);
					break;
				case 'n':           /* normal */
					/* eat up rest of line */
					fscanf(fp,"%f %f %f",&v1,&v2,&v3);
					vertex_list[vn].normal[0]=v1;
					vertex_list[vn].normal[1]=v2;
					vertex_list[vn].normal[2]=v3;
					vn++;
					break;
				case 't':           /* texcoord */
					fscanf(fp,"%f %f %f",&v1,&v2,&v3);
					break;
				default:
					break;
				}
			break;
			}
		case 'f':
			FACE ftemp;
			int a,b,c;
			fscanf(fp,"%d/%d/%d",&a,&b,&c);
			ftemp.index[0]=a-1;
			fscanf(fp,"%d/%d/%d",&a,&b,&c);
			ftemp.index[1]=a-1;
			fscanf(fp,"%d/%d/%d",&a,&b,&c);
			ftemp.index[2]=a-1;
			fscanf(fp,"%d/%d/%d",&a,&b,&c);
			ftemp.index[3]=a-1;
			ftemp.bTriangle=false;
			face_list.push_back(ftemp);
			break;
		default:
             fgets(buf, sizeof(buf), fp);
			 break;
		}
	}
	fclose(fp);
	calculateNormals();
}

void ImportObj::setTexture(GLTexture* text)
{
	texture=text;
}

ImportObj::~ImportObj(void)
{

}

void ImportObj::draw(void)
{
	int findex;

	if(texture) 	texture->Use();
	glPushMatrix();
	glScalef(this->scalef[0], this->scalef[1], this->scalef[2]);
	glTranslatef(this->translatef[0], this->translatef[1], this->translatef[2]);
	glRotatef(this->rotatef[0], this->rotatef[1], this->rotatef[2], this->rotatef[3]);
	glBegin(GL_QUADS);
	//glBegin(GL_TRIANGLES);
	//GLfloat temp=1.0/face_count;
	for(findex=0;findex<face_list.size();findex++)
	{
		//定义法向量
		glNormal3fv(face_list[findex].normal);
		glTexCoord2f(0.0,0.0);
		glVertex3fv(vertex_list[face_list[findex].index[0]].xyz);
		glTexCoord2f(0.0,1.0);
		glVertex3fv(vertex_list[face_list[findex].index[1]].xyz);
		glTexCoord2f(1.0,1.0);
		glVertex3fv(vertex_list[face_list[findex].index[2]].xyz);
		glTexCoord2f(1.0,0.0);
		glVertex3fv(vertex_list[face_list[findex].index[3]].xyz);

	}
	glEnd();
	glFlush();


	glPopMatrix();
	if(texture) glDisable(GL_TEXTURE_2D);		//important
}

void ImportObj::calculateNormal(float *out, float *a, float *b, float *c)
{
		float v1[3], v2[3];

	// calculate two vectors from the three points 

	v1[0]=a[0]-b[0];
	v1[1]=a[1]-b[1];
	v1[2]=a[2]-b[2];

	v2[0]=a[0]-c[0];
	v2[1]=a[1]-c[1];
	v2[2]=a[2]-c[2];
	// take the cross product  

	out[0]=v1[1]*v2[2]-v1[2]*v2[1];
	out[1]=v1[2]*v2[0]-v1[0]*v2[2];
	out[2]=v1[0]*v2[1]-v1[1]*v2[0];

	// normalize result 
/*	float temp;
	temp=sqrt(out[0]*out[0]+out[1]*out[1]+out[2]*out[2]);
	out[0]=out[0]/temp;
	out[1]=out[1]/temp;
	out[2]=out[2]/temp;*/
	glEnable(GL_NORMALIZE);

}
void ImportObj::calculateNormals(void)
{
	// first, calculate the normal for each face 
	
	for (int i=0; i<face_list.size();i++)
	{
		calculateNormal(face_list[i].normal , vertex_list[face_list[i].index[0]].xyz , vertex_list[face_list[i].index[1]].xyz ,
						vertex_list[face_list[i].index[2]].xyz );
	}
	// for each vertex, initialize the vertex   normal
	/*for (int i=0; i<vertex_list.size(); i++)
	{
		vertex_list[i].normal[0]=0.0;
		vertex_list[i].normal[1]=0.0;
		vertex_list[i].normal[2]=0.0;
	}*/

	// for each vertex, sum the surface normals of the surrounding faces
	int numVer;
	for (int i=0; i<face_list.size(); i++)
	{
		numVer=4;
		if(face_list[i].bTriangle) numVer=3;	
		for (int j=0; j<numVer; j++)
		{
			vertex_list[face_list[i].index[j]].normal[0] = vertex_list[face_list[i].index[j]].normal[0] + face_list[i].normal[0];
			vertex_list[face_list[i].index[j]].normal[1] = vertex_list[face_list[i].index[j]].normal[1] + face_list[i].normal[1];
			vertex_list[face_list[i].index[j]].normal[2] = vertex_list[face_list[i].index[j]].normal[2] + face_list[i].normal[2];

		}
	}
}

void ImportObj::setScalef(GLfloat x){
    for(int i=0;i<3;i++){
        this->scalef[i]=x;
    }
}

void ImportObj::setTranslatef(GLfloat x, GLfloat y, GLfloat z){
    this->translatef[0]=x;
    this->translatef[1]=y;
    this->translatef[2]=z;
}

void ImportObj::setRotatef(GLfloat angel, GLfloat x, GLfloat y, GLfloat z){
    this->rotatef[0]=angel;
    this->rotatef[1]=x;
    this->rotatef[2]=y;
    this->rotatef[3]=z;
}
