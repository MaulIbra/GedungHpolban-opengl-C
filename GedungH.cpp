#include <GL/glut.h>
#include <math.h>
#include <iostream>

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f,ly=1.0f;
// XZ position of the camera
float x=0.0f,z=100.0f,y=1.0f;

//storage gambar
GLuint texture[35];

//struct gambar
struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
};

int ImageLoad(char *filename, Image *image) {
	FILE *file;
	unsigned long size; // ukuran image dalam bytes
	unsigned long i; // standard counter.
	unsigned short int plane; // number of planes in image

	unsigned short int bpp; // jumlah bits per pixel
	char temp; // temporary color storage for var warna sementara untuk memastikan filenya ada


	if ((file = fopen(filename, "rb")) == NULL) {
		printf("File Not Found : %s\n", filename);
		return 0;
	}
	// mencari file header bmp
	fseek(file, 18, SEEK_CUR);
	// read the width
	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}
	//printf("Width of %s: %lu\n", filename, image->sizeX);
	// membaca nilai height
	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}
	//printf("Height of %s: %lu\n", filename, image->sizeY);
	//menghitung ukuran image(asumsi 24 bits or 3 bytes per pixel).

	size = image->sizeX * image->sizeY * 3;
	// read the planes
	if ((fread(&plane, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
	}
	if (plane != 1) {
		printf("Planes from %s is not 1: %u\n", filename, plane);
		return 0;
	}
	// read the bitsperpixel
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);

		return 0;
	}
	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}
	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);
	// read the data.
	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}
	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}
	for (i = 0; i < size; i += 3) { // membalikan semuan nilai warna (gbr - > rgb)
		temp = image->data[i];
		image->data[i] = image->data[i + 2];
		image->data[i + 2] = temp;
	}
	// we're done.
	return 1;
}

Image * loadTexture(char *filename) {
	Image *image1;
	
	// alokasi memmory untuk tekstur
	image1 = (Image *) malloc(sizeof(Image));
	if (image1 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad(filename, image1)) {
		exit(1);
	}
	return image1;
}

void generateTexture(Image *imageTexture,int i){
	//texture 1
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imageTexture->sizeX, imageTexture->sizeY, 0, GL_RGB,
	GL_UNSIGNED_BYTE, imageTexture->data);
}


void init(){
        glClearColor(0.5, 0.5, 0.5, 0.0);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
       
       Image *image1 = loadTexture("tiang.bmp");
	   Image *image2 = loadTexture("tiangAtas.bmp");
	   Image *image3 = loadTexture("polban.bmp");
	   Image *image4 = loadTexture("pondasi.bmp");
	   Image *image5 = loadTexture("tiangAtas2.bmp");
	   Image *image6 = loadTexture("cream.bmp");
       Image *image7 = loadTexture("coklat_tua.bmp");
       Image *image8 = loadTexture("kaca.bmp");
       Image *image9 = loadTexture("pintuSatu.bmp");
       Image *image10 = loadTexture("pintuDua.bmp");
       Image *image11 = loadTexture("langit.bmp");
       
	   if (image1 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}

       if (image2 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
	
	if (image3 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
	if (image4 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}if (image5 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}if (image6 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
	
	glGenTextures(35,texture);
	
	generateTexture(image1,0);
	generateTexture(image2,1);
	generateTexture(image3,2);
	generateTexture(image4,3);
	generateTexture(image5,4);
	generateTexture(image6,5);
	generateTexture(image7,6);
	generateTexture(image8,7);
	generateTexture(image9,8);
	generateTexture(image10,9);
	generateTexture(image11,10);
	
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);
}



void limas(float x, float y, float z){

	//Sisi-sisi limas
	glBegin(GL_TRIANGLES);
				glTexCoord2f(0.0, 0.0);glVertex3f(-x/2,y/2,z/2);
				glTexCoord2f(0.0, 1.0);glVertex3f(-x/2,y/2,-z/2);
				glTexCoord2f(1.0, 1.0);glVertex3f(0,y*2,0);
				
				glTexCoord2f(0.0, 0.0);glVertex3f(-x/2,y/2,z/2);
				glTexCoord2f(0.0, 1.0);glVertex3f(x/2,y/2,z/2);
				glTexCoord2f(1.0, 1.0);glVertex3f(0,y*2,0);
					
				glTexCoord2f(0.0, 0.0);glVertex3f(x/2,y/2,-z/2);
				glTexCoord2f(0.0, 1.0);glVertex3f(0,y*2,0);
				glTexCoord2f(1.0, 1.0);glVertex3f(x/2,y/2,z/2);
			
				glTexCoord2f(0.0, 0.0);glVertex3f(-x/2,y/2,-z/2);
				glTexCoord2f(0.0, 1.0);glVertex3f(0,y*2,0);
				glTexCoord2f(1.0, 1.0);glVertex3f(x/2,y/2,-z/2);
	glEnd();

}

void drawCubePerbagian(int x,int y,int z, int bagianKubus){
	glBegin(GL_QUADS);
		
		if(bagianKubus == 1){
			// front face
                glTexCoord2f(0.0, 0.0);glVertex3f(-x/2,-y/2,z/2);
            	glTexCoord2f(1.0, 0.0);glVertex3f(x/2,-y/2,z/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(x/2,y/2,z/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(-x/2,y/2,z/2);
		}else if (bagianKubus==2){
			// back face
                glTexCoord2f(1.0, 0.0);glVertex3f(-x/2,-y/2,-z/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(-x/2,y/2,-z/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(x/2,y/2,-z/2);
                glTexCoord2f(0.0, 0.0);glVertex3f(x/2,-y/2,-z/2);
		}else if (bagianKubus==3){
			// right face
                glTexCoord2f(1.0, 0.0);glVertex3f(x/2,-y/2,-z/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(x/2,y/2,-z/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(x/2,y/2,z/2);
                glTexCoord2f(0.0, 0.0);glVertex3f(x/2,-y/2,z/2);
		}else if (bagianKubus==4){
			// left face
                glTexCoord2f(0.0, 0.0);glVertex3f(-x/2,-y/2,-z/2);
                glTexCoord2f(1.0, 0.0);glVertex3f(-x/2,-y/2,z/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(-x/2,y/2,z/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(-x/2,y/2,-z/2);
		}else if (bagianKubus==5){
			// top face
                glTexCoord2f(0.0, 1.0);glVertex3f(-x/2,y/2,-z/2);
                glTexCoord2f(0.0, 0.0);glVertex3f(-x/2,y/2,z/2);
                glTexCoord2f(1.0, 0.0);glVertex3f(x/2,y/2,z/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(x/2,y/2,-z/2);
		}else if (bagianKubus==6){
			// bottom face
                glTexCoord2f(1.0, 1.0);glVertex3f(-x/2,-y/2,-z/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(x/2,-y/2,-z/2);
                glTexCoord2f(0.0, 0.0);glVertex3f(x/2,-y/2,z/2);
                glTexCoord2f(1.0, 0.0);glVertex3f(-x/2,-y/2,z/2);
		}
                                
    glEnd();
}

void drawCube(float x,float y,float z){
	glBegin(GL_QUADS);
                // front face
                glTexCoord2f(0.0, 0.0);glVertex3f(-x/2,-y/2,z/2);
            	glTexCoord2f(1.0, 0.0);glVertex3f(x/2,-y/2,z/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(x/2,y/2,z/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(-x/2,y/2,z/2);
                // left face
                glTexCoord2f(0.0, 0.0);glVertex3f(-x/2,-y/2,-z/2);
                glTexCoord2f(1.0, 0.0);glVertex3f(-x/2,-y/2,z/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(-x/2,y/2,z/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(-x/2,y/2,-z/2);
                // back face
                glTexCoord2f(1.0, 0.0);glVertex3f(-x/2,-y/2,-z/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(-x/2,y/2,-z/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(x/2,y/2,-z/2);
                glTexCoord2f(0.0, 0.0);glVertex3f(x/2,-y/2,-z/2);
                // right face
                glTexCoord2f(1.0, 0.0);glVertex3f(x/2,-y/2,-z/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(x/2,y/2,-z/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(x/2,y/2,z/2);
                glTexCoord2f(0.0, 0.0);glVertex3f(x/2,-y/2,z/2);
                // top face
                glTexCoord2f(0.0, 1.0);glVertex3f(-x/2,y/2,-z/2);
                glTexCoord2f(0.0, 0.0);glVertex3f(-x/2,y/2,z/2);
                glTexCoord2f(1.0, 0.0);glVertex3f(x/2,y/2,z/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(x/2,y/2,-z/2);
                // bottom face
                glTexCoord2f(1.0, 1.0);glVertex3f(-x/2,-y/2,-z/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(x/2,-y/2,-z/2);
                glTexCoord2f(0.0, 0.0);glVertex3f(x/2,-y/2,z/2);
                glTexCoord2f(1.0, 0.0);glVertex3f(-x/2,-y/2,z/2);
    glEnd();
}


void drawObject(float xtrans, float ytrans, float ztans, float x, float y, float z, int numberTexture){

	glPushMatrix();
	glTranslatef(xtrans,ytrans,ztans);
	glBindTexture(GL_TEXTURE_2D, texture[numberTexture]);
	drawCube(x,y,z);
	glPopMatrix();

}

void drawObjectTransparant(float xtrans, float ytrans, float ztans, float x, float y, float z, int PositionCube, int numberTexture){
	
	if(PositionCube!= 0){
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture[numberTexture]);
		glTranslatef(xtrans,ytrans,ztans);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, 0.5);
		drawCubePerbagian(x,y,z,PositionCube);
		glDisable(GL_BLEND);
		glPopMatrix();
	}
	else{
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture[numberTexture]);
		glTranslatef(xtrans,ytrans,ztans);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, 0.5);
		drawCube(x,y,z);
		glDisable(GL_BLEND);
		glPopMatrix();	
	}
	
}

void changeSize(int w, int h)
{
	
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
	h = 1;
	float ratio = w * 1.0 / h;
	
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	
	// Reset Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	
	// Set the correct perspective.
	gluPerspective(90.0f, ratio, 0.1f, 300.0f);
	
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// ============= end of Texture ============= //

void pondasi(){
	
	//pondasi ruangan perpustakaan
	drawObject(8.5,2,0,63,4,20,3);
	
	//pondasi ruangan bangunan kelas
	drawObject(45,2,26.5,20,4,73,3);
	
	//pondasi tiang bangunan perpustakaan
	drawObject(-19,2,12,2,4,4,3);
	
	// pondasi tiang atas bangunan perpustakaan dekat bangunan icon polban
	drawObject(-5,2,12,2,4,4,3);
	
	// pondasi tiang atas bangunan perpustakaan nyambung bangunan icon polban
	drawObject(9,2,12,2,4,4,3);
	
	//pondasi perpustakaan bagian depan
	drawObject(-24,2,9.5,2,4,1,3);
	
	//pondasi perpustakaan bagian depan
	drawObject(-24,2,4,2,4,2,3);
	
	//pondasi perpustakaan bagian depan
	drawObject(-24,2,-4,2,4,2,3);
	
	//pondasi perpustakaan bagian depan
	drawObject(-24,2,-9.5,2,4,1,3);
	
	//pondasi jendela ruang kelas 1
	drawObject(-12,2,12,12,4,2,3);
	
	//pondasi jendela ruang kelas 2
	drawObject(2,2,12,12,4,2,3);
	
	//pondasi tiang bangunan ruangan kelas dekat icon polban
	drawObject(45,2,45,28,4,2,3);
	
	//pondasi tiang bangunan ruangan kelas nyambung icon polban
	drawObject(45,2,31,28,4,2,3);
	
	//pondasi tiang bangunan ruangan kelas
	drawObject(45,2,59,28,4,2,3);
	
	//pondasi jendela ruang kelas 1
	drawObject(33,2,52,2,4,12,3);
	
	//pondasi jendela ruang kelas 2
	drawObject(33,2,38,2,4,12,3);
	
	//pondasi tiang depan
	drawObject(35.5,2,64,1,4,2,3);
	
	//pondasi tiang depan
	drawObject(41,2,64,2,4,2,3);
	
	//pondasi tiang depan
	drawObject(49,2,64,2,4,2,3);
	
	//pondasi tiang depan
	drawObject(54.5,2,64,1,4,2,3);
	
	//lantai pondasi kaca depan
	drawObject(38,2,62.5,4,4,2,3);
	
	//lantai pondasi kaca depan 
	drawObject(52,2,62.5,4,4,2,3);
	
	//pondasi kanan bawah icon gedung H
	drawObject(28,2,33,4,4,4,3);
	
	//pondasi kiri atas icon gedung H
	drawObject(12,2,17,4,4,4,3);
	
	//pondasi kanan atas icon gedung H
	drawObject(28,2,17,4,4,4,3);
	
	//pondasi kiri bawah icon gedung H
	drawObject(12,2,33,4,4,4,3);
}


///============== end of pondasi bangunan ============ ///


void balcon(){
	
	// ============================================== BALCON PERPUSTAKAAN === //
	
	//balcon lantai 1 bangunan perpustakaan
	drawObject(-12,13,0,24,4,32,3);
	
	//balcon lantai 2 bangunan perpustakaan
	drawObject(-12,22,0,24,4,32,3);
	
	//balcon lantai 3 bangunan perpustakaan
	drawObject(3,31,0,54,4,32,3);
	
	// ================================================== BALCON KELAS === //
	
	//balcon lantai 1
	drawObject(44.75,13,52,32,4,24,3);
	// balcon lantai 2
	drawObject(44.75,22,52,32,4,24,3);	
	//balcon lantai 3
	drawObject(44.75,31,37,32,4,54,3);
	
	// balcon bagian depan
	drawObject(45,13,66,6,4,4,3);
	// balcon bagian depan
	drawObject(45,22,66,6,4,4,3);
	// balcon bagian depan
	drawObject(45,31,66,6,4,4,3);
	
}


 void tiang(){
 	
 	//============================================= TIANG PERPUSTAKAAN ==//
 	
	//tiang atas ujung bagian bawah
	drawObject(-19,21.5,12,2,35,4,5);
	
	// tiang atas dekat limas bagian bawah
	drawObject(-5,21.5,12,2,35,4,5);
	
	// tiang atas nyambung limas bagian bawah
	drawObject(9,21.5,12,2,35,4,5);
 	
 	//============================================= TIANG KELAS ==//
 		
	//===== samping kiri ===//

	//tiang bawah ujung bagian bawah
	drawObject(33.5,21.5,59,4.5,35,2,5);
	
	// tiang bawah dekat limas bagian bawah
	drawObject(33.5,21.5,45,4.5,35,2,5);
	
	// tiang bawah nyambung ke limas bagian bawah
	drawObject(33.5,21.5,31,4.5,35,2,5);
	
	//== samping kanan ==//
	//tiang bawah ujung bagian bawah
	drawObject(56.75,21.5,59,4.5,35,2,5);
	
	// tiang bawah dekat limas bagian bawah
	drawObject(56.75,21.5,45,4.5,35,2,5);
	
	// tiang bawah nyambung ke limas bagian bawah
	drawObject(56.5,21.5,31,4.5,35,2,5);
	
	//================================================ TIANG ICON GEDUNG H =======//
		//tiang kiri atas
	drawObject(12,14,17,4,20,4,0);
	//tiang kanan atas
	drawObject(28,14,17,4,20,4,0);
	//tiang kiri bawah
	drawObject(12,14,33,4,20,4,0);
	//tiang kanan bawah
	drawObject(28,14,33,4,20,4,0);
	
 }
 
 void atap(){
	
	//================================================ ATAP PERPUSTAKAAN == //
	
		// atap bagian ke 1 //
	
	//atap 1 kelas
	drawObject(3,38.5,0,54,1,32,3);
	
	//atap 1 kelas
	drawObject(-26,38.5,0,4,1,26,3);
	
	//atap 1 kelas
	drawObject(-29,38.5,0,2,1,10,3);
	
	
	//atap bagian ke 2 //
	
	//atap 2 kelas
	drawObject(3,43.5,0,54,1,32,3);
	
	//atap 2 kelas
	drawObject(-27,43.5,0,6,1,26,3);
	
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBegin(GL_POLYGON); // Draw A Quad
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-24.0f, 44.0f, -16.0f); //depan kiri
		glTexCoord2f(1.0f, 0.0f);glVertex3f(-18.75f, 60.0f,0.0f); // depan tengah
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-24.0f, 44.0f,16.0f); //depan kanan
		glEnd();
 	glPopMatrix();
 	
	 glPushMatrix();
 		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_POLYGON); // Draw A Quad
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-24.0f, 44.0f, -16.0f); //depan kiri
		glTexCoord2f(0.0f, 1.0f);glVertex3f(44.75f, 44.0f, -16.0f); //belakang kiri
		glTexCoord2f(0.0f, 0.0f);glVertex3f(44.75f, 60.0f, 0.0f); // belakang tengah
		glTexCoord2f(1.0f, 0.0f);glVertex3f(-18.75f, 60.0f,0.0f); // depan tengah
		glEnd();
	 glPopMatrix();	
	 
	glPushMatrix();
 		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_POLYGON); // Draw A Quad
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-24.0f, 44.0f,16.0f); //depan kanan
		glTexCoord2f(1.0f, 0.0f);glVertex3f(44.75f, 44.0f,  16.0f); //belakang kanan
		glTexCoord2f(0.0f, 0.0f);glVertex3f(44.75f, 60.0f, 0.0f); // belakang tengah
		glTexCoord2f(1.0f, 0.0f);glVertex3f(-18.75f, 60.0f,0.0f); // depan tengah
		glEnd();
 	glPopMatrix();
// 	
	 glPushMatrix();
 		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_POLYGON); // Draw A Quad
		glTexCoord2f(0.0f, 1.0f);glVertex3f(44.75f, 44.0f, -16.0f); //belakang kiri
		glTexCoord2f(0.0f, 0.0f);glVertex3f(44.75f, 60.0f, 0.0f); // belakang tengah
		glTexCoord2f(1.0f, 0.0f);glVertex3f(44.75f, 44.0f,  16.0f); //belakang kanan
		glEnd();
 	glPopMatrix();
	
	// ================================================== ATAP KELAS == //
		
	//atap 1 kelas
	drawObject(44.75,38.5,37,32,1,54,3);
	
	//atap 1 kelas
	drawObject(45.25,38.5,66,26,1,4,3);
	
	//atap 1 kelas
	drawObject(45,38.5,69,10,1,2,3);
	
	
	//atap 2 kelas
	drawObject(44.75,43.5,25,32,1,78,3);
	
	//atap 2 kelas
	drawObject(45.25,43.5,67,26,1,6,3);
		 
		 
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBegin(GL_POLYGON); // Draw A Quad
		glTexCoord2f(0.0f, 1.0f);glVertex3f(28.75f, 44.0f, 64.0f); //depan kiri
		glTexCoord2f(1.0f, 0.0f);glVertex3f(44.75f, 60.0f, 58.0f); // depan tengah
		glTexCoord2f(0.0f, 0.0f);glVertex3f(60.75f, 44.0f, 64.0f); //depan kanan
		glEnd();
 	glPopMatrix();
 	
	 glPushMatrix();
 		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_POLYGON); // Draw A Quad
		glTexCoord2f(0.0f, 1.0f);glVertex3f(28.75f, 44.0f, 64.0f); //depan kiri
		glTexCoord2f(1.0f, 0.0f);glVertex3f(28.75f, 44.0f, -16.0f); //belakang kiri
		glTexCoord2f(0.0f, 1.0f);glVertex3f(44.75f, 60.0f, -10.0f); // belakang tengah
		glTexCoord2f(1.0f, 1.0f);glVertex3f(44.75f, 60.0f, 58.0f); // depan tengah
		glEnd();
	 glPopMatrix();	
	 
	glPushMatrix();
 		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_POLYGON); // Draw A Quad
		glTexCoord2f(0.0f, 1.0f);glVertex3f(60.75f, 44.0f, 64.0f); //depan kanan
		glTexCoord2f(1.0f, 0.0f);glVertex3f(60.75f, 44.0f, -16.0f); //belakang kanan
		glTexCoord2f(0.0f, 1.0f);glVertex3f(44.75f, 60.0f, -10.0f); // belakang tengah
		glTexCoord2f(1.0f, 1.0f);glVertex3f(44.75f, 60.0f, 58.0f); // depan tengah
		glEnd();
 	glPopMatrix();
 	
	 glPushMatrix();
 		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_POLYGON); // Draw A Quad
		glTexCoord2f(0.0f, 1.0f);glVertex3f(28.75f, 44.0f, -16.0f); //belakang kiri
		glTexCoord2f(1.0f, 0.0f);glVertex3f(60.75f, 44.0f, -16.0f); //belakang kanan
		glTexCoord2f(0.0f, 0.0f);glVertex3f(44.75f, 60.0f, -10.0f); // belakang tengah
		glEnd();
 	glPopMatrix();

	
 }
 
 void jendela(){
 	
 	// ============================================================================= JENDELA PERPUSTAKAAN == //
 	
 	
	//lantai 1 bagian kiri
	drawObjectTransparant(-12,7,10,12,6,2,1,7);
	//lantai 2 bagian kiri
	drawObjectTransparant(-12,17,10,12,4,2,1,7);
	//lantai 3 bagian kiri
	drawObjectTransparant(-12,26,10,12,4,2,1,7);
	//lantai 4 bagian kiri
	drawObjectTransparant(-12,35,10,12,4,2,1,7);
	
	//lanta 1 bagian kanan
	drawObjectTransparant(2,7,10,12,6,2,1,7);
	//lantai 2 bagian kanan
	drawObjectTransparant(2,17,10,12,4,2,1,7);
	//lantai 3 bagian kanan
	drawObjectTransparant(2,26,10,12,4,2,1,7);
	//lantai 4 bagian kanan
	drawObjectTransparant(2,35,10,12,4,2,1,7);
	
	// ================================================================================== JENDELA KELAS == //
	
		//lantai 1
	drawObjectTransparant(34.05,7,52,2.05,6,12,0,7);
	//lantai 2
	drawObjectTransparant(34.05,17,52,2.05,4,12,0,7);
	//lantai 3
	drawObjectTransparant(34.05,26,52,2.05,4,12,0,7);
	//lantai 4
	drawObjectTransparant(34.05,35,52,2.05,4,12,0,7);
	
	//================//
	
	//lanta 1
	drawObjectTransparant(34.05,7,38,2.05,6,12,0,7);
	//lantai 2
	drawObjectTransparant(34.05,17,38,2.05,4,12,0,7);
	//lantai 3
	drawObjectTransparant(34.05,26,38,2.05,4,12,0,7);
	//lantai 4
	drawObjectTransparant(34.05,35,38,2.05,4,12,0,7);
	
	
	//===== bagian depan 1===///
	//lantai 1
	drawObjectTransparant(38,7,62.5,4,6,2,0,7);
	//lantai2
	drawObjectTransparant(38,17,62.5,4,4,2,0,7);
	//lantai3
	drawObjectTransparant(38,26,62.5,4,4,2,0,7);
	//lantai3
	drawObjectTransparant(38,35,62.5,4,4,2,0,7);
	
	//==== bagian depan ke 2
	
	//lantai2
	drawObjectTransparant(45,17,62.5,6,4,2,0,7);
	//lantai3
	drawObjectTransparant(45,26,62.5,6,4,2,0,7);
	//lantai4
	drawObjectTransparant(45,35,62.5,6,4,2,0,7);
	
	
	
	//==== bagian depan ke 3
	
	//lantai 1
	drawObjectTransparant(52,7,62.5,4,6,2,0,7);
	//lantai2
	drawObjectTransparant(52,17,62.5,4,4,2,0,7);
	//lantai3
	drawObjectTransparant(52,26,62.5,4,4,2,0,7);
	//lantai4
	drawObjectTransparant(52,35,62.5,4,4,2,0,7);
	
 }

void frameJendela(){
	//============================================ BAGIAN PERPUSTAKAAN ==//
	
		//lantai 1 bagian kiri
	drawObject(-12,10.5,10,12,1,2,5);
	//lantai 2 bagian kiri
	drawObject(-12,19.5,10,12,1,2,5);
	//lantai 3 bagian kiri
	drawObject(-12,28.5,10,12,1,2,5);
	//lantai 4 bagian kiri
	drawObject(-12,37.5,10,12,1,2,5);
	
	
	//lantai 1 bagian kanan
	drawObject(2,10.5,10,12,1,2,5);
	//lantai 2 bagian kanan
	drawObject(2,19.5,10,12,1,2,5);
	//lantai 3 bagian kanan
	drawObject(2,28.5,10,12,1,2,5);
	//lantai 4 bagian kanan
	drawObject(2,37.5,10,12,1,2,5);
	
	
	//lantai 1 bagian balcon
	drawObject(4,13,10,8,4,2,5);
	//lantai 2 bagian balcon
	drawObject(4,22,10,8,4,2,5);
	
	//================================================= BAGIAN KELAS ==//
	
		//lantai 1
	drawObject(38,12.5,62.5,4,5,2,5);
	//lantai2
	drawObject(38,21.5,62.5,4,5,2,5);
	//lantai3
	drawObject(38,29,62.5,4,2,2,5);
	//lantai4
	drawObject(38,37,62.5,4,2,2,5);
	
	//=== frame tengah depan ==//
	
	//lantai2
	drawObject(45,21.5,62.5,6,5,2,5);
	//lantai3
	drawObject(45,29,62.5,6,2,2,5);
	//lantai4
	drawObject(45,37,62.5,6,2,2,5);

		
	
	//=== frame ke 2 ====//
	
	//lantai 1
	drawObject(52,12.5,62.5,4,5,2,5);
	//lantai2
	drawObject(52,21.5,62.5,4,5,2,5);
	//lantai3
	drawObject(52,29,62.5,4,2,2,5);
	//lantai4
	drawObject(52,37,62.5,4,2,2,5);
	
	
	//==== frame bagian samping ==//
	
	//lantai 1
	drawObject(34.05,10.5,52,2.05,1,12,5);
	//lantai 2
	drawObject(34.05,19.5,52,2.05,1,12,5);
	//lantai 3
	drawObject(34.05,28.5,52,2.05,1,12,5);
	//lantai 4
	drawObject(34.05,37.5,52,2.05,1,12,5);
	
	
	//==== frame bagian samping ==//
	
	//lantai 1
	drawObject(34.05,10.5,38,2.05,1,12,5);
	//lantai 2
	drawObject(34.05,19.5,38,2.05,1,12,5);
	//lantai 3
	drawObject(34.05,28.5,38,2.05,1,12,5);
	//lantai 4
	drawObject(34.05,37.5,38,2.05,1,12,5);
	
	//=== frame balcon ==//
	drawObject(34.05,13,36,2.05,4,8,5);
	drawObject(34.05,22,36,2.05,4,8,5);
	
}



void bangunanPerpustakaan(){
	//bagian ruangan perpustakaan
	drawObject(8.5,24,0,63,40,20,6);	
	drawObject(-24,24,9.5,2,40,1,6);
	drawObject(-24,24,4,2,40,1,6);
	drawObject(-24,24,-4,2,40,1,6);
	drawObject(-24,24,-9.5,2,40,1,6);

}

void pintu(){
	//== BAGIAN PINTU KELAS == //
	
	//== pintu depan lantai 1 ==//
	drawObject(45,7.5,63,6,7,0.4,5);
	drawObject(45,2,63,6,4,0.4,3);
	//bagian pintu
	drawObjectTransparant(45,7,63,4,6,0.5,0,9);
	//end of pintu depan //	
	
	//pintu utama 
	drawObject(35,7.5,24.5,2,7,9,5);
	drawObject(35,6.5,24.5,2.05,6,7,9);
	
	
	//=== BAGIAN PERPUSTAKAAN ==//
	drawObject(21,7.5,10,10,7,2,5);
	drawObject(21,6.5,10,8,6,2.05,9);
}


void bangunanKelas(){
	//bagian ruangan bangunana kanan
	drawObject(45,24,26.5,20,40,73,6);
	
	//bagian depan kelas
	drawObject(35.5,24,64,1,40,2,6);
	
	//bagian depan kelas;
	drawObject(41,24,64,2,40,2,6);
	
	//bagian depan kelas
	drawObject(49,24,64,2,40,2,6);
	
	//bagian depan kelas
	drawObject(54.5,24,64,1,40,2,6);
}



// ====== end of bangunan kelas ======== //

void tangga(){
	//===TANGGA ICON GEDUNG H == //
	//tangga 1
	drawObject(20,0,25,22,2,22,1);
	//tangga 2
	drawObject(20,1,25,18,2,18,1);
	
}

void bangunanIconGedungH(){
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTranslatef(20,19,25);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 0.5);
	limas(18,10,18);
	glDisable(GL_BLEND);
	glPopMatrix();
	
	//logo polban
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTranslatef(21,18,25);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 0.5);
	glBegin(GL_QUADS);
                // front face
                glTexCoord2f(0.0, 0.0);glVertex3f(-18/2,-12/2,18/2);
            	glTexCoord2f(1.0, 0.0);glVertex3f(18/2,-12/2,18/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(18/2,12/2,18/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(-18/2,12/2,18/2);
                
                // left face
                glTexCoord2f(0.0, 0.0);glVertex3f(-18/2,-12/2,-18/2);
                glTexCoord2f(1.0, 0.0);glVertex3f(-18/2,-12/2,18/2);
                glTexCoord2f(1.0, 1.0);glVertex3f(-18/2,12/2,18/2);
                glTexCoord2f(0.0, 1.0);glVertex3f(-18/2,12/2,-18/2);
    glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();
	
			
	glPushMatrix();
	glTranslatef(20,22,25);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	drawCube(22,4,22);
	glPopMatrix();
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTranslatef(21,12,25);
	drawCube(18,2,18);
	glPopMatrix();
	
	//bagian linmas
}


// ====== end of bangunan icon gedung H //


void renderScene(void) {

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, y, z,
			x+lx, ly,  z+lz,
			0.0f, 1.0f,  0.0f);

        // Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-150.0f, 0.5f, -150.0f);
		glVertex3f(-150.0f, 0.5f,  150.0f);
		glVertex3f( 150.0f, 0.5f,  150.0f);
		glVertex3f( 150.0f, 0.5f, -150.0f);
	glEnd();
	
	
	//sky box
	glPushMatrix();
	glTranslatef(50,50,50);
	glBindTexture(GL_TEXTURE_2D, texture[10]);
	drawCube(200,100,200);
	glPopMatrix();

  
  	// bagian bangunan
  	pondasi();
	balcon();
	tiang();
	atap();
	jendela();
	frameJendela();
	pintu();
	tangga();
	bangunanPerpustakaan();
	bangunanKelas();
	bangunanIconGedungH();
	
	 //ATAP BARAT DEPAN
	glutSwapBuffers();
}



void processNormalKeys(unsigned char key, int x, int y)
{

if (key == 27)
exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.8f;

	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.05f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.05f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
		case GLUT_KEY_PAGE_UP:
			y += 0.50f;
			ly += 0.50f;
			break;
		case GLUT_KEY_PAGE_DOWN :
			y -= 0.50f;
			ly -= 0.50f;
			break;
	}
}


int main(int argc, char **argv) {

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("GEDUNG H POLBAN");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	// enter GLUT event processing cycle
	init();
	glutMainLoop();

	return 1;
}
