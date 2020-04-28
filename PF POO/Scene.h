#ifndef __Escena
#define __Escena

#include <gl\GLU.h>
#include <gl\GL.h>
#include "SkyDome.h"
#include "Terrain.h"
#include "Model.h"
#include "Water.h"
#include "Billboard.h"
#include "Fog.h"
#include "Camera.h"
#include <thread>
#include <vector>
#define BILLSIZE 50
//BIENVENIDO AL ARCHIVO MAS IMPORTANTE DE TU PROYECTO
class Scene : public Camera {
public:
	HWND hWnd = 0;

	short int skyIndex, lightIndex;
	float skyRotation;

	SkyDome *skyDome = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//cloudysky.jpg");
	Terrain *terrain = new Terrain(hWnd, L"Imagenes//mainTerrain.bmp", L"Imagenes//texturaCesped.jpg", L"Imagenes//texturaCesped.jpg", 936, 936);
	Water *lago = new Water(hWnd, L"Imagenes//waterMap.bmp", L"Imagenes//agua.jpg", 1024, 1024);
	GLfloat AmbMat[4] = { 255, 255, 220, 1 };

	EDXFramework::Model* Gate;
	EDXFramework::Model* Car;
	EDXFramework::Model* Chair;
	EDXFramework::Model* WTable;
	EDXFramework::Model* Escritorio;
	EDXFramework::Model* Telefono;
	EDXFramework::Model* Laptop;
	EDXFramework::Model* GasCan;
	EDXFramework::Model* Fichero;
	EDXFramework::Model* TCone;
	EDXFramework::Model* Extintor;
	EDXFramework::Model* Lamp;
	EDXFramework::Model* KeyItem;
	EDXFramework::Model* Tower;
	EDXFramework::Model* Building;
	EDXFramework::Model* Enemy;
	EDXFramework::Model* Enemy2;
	EDXFramework::Model* PlayerHands;

	Billboard *billBoard[BILLSIZE];

	Scene(HWND hWnd)
	{
		this->hWnd = hWnd;
		skyIndex = lightIndex, skyRotation = 0;

		GLfloat AmbPos[] = { 0, 400, 400, 1 };

		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, AmbPos);

		PlayerHands = new EDXFramework::Model("Modelos//Character//playerHands.obj", "Modelos//Character//Arm_Base_Color.bmp", 1);
		KeyItem = new EDXFramework::Model("Modelos//KeyItem//KeyItem.obj", "Modelos//KeyItem//KeyItem.bmp", 1);
		Car = new EDXFramework::Model("Modelos//Car//mtCar.obj", "Modelos//Car//car.bmp", 1);
		Enemy = new EDXFramework::Model("Modelos//ENEMY//smallEnemy.obj", "Modelos//ENEMY//lizard_diffuse.bmp", 1);
		Enemy2 = new EDXFramework::Model("Modelos//ENEMY//redEnemy.obj", "Modelos//ENEMY//inside1.bmp", 1);
		Laptop = new EDXFramework::Model("Modelos//Laptop2//Lowpoly Old Notebook.obj", "Modelos//Laptop2//Notebook Color.bmp", 1);
		Telefono = new EDXFramework::Model("Modelos//Telefono//10109_Cordless Phone_v2_Iteration2.obj", "Modelos//Telefono//10109_Cordless Phone_v1_Diffuse.bmp", 1);
		Escritorio = new EDXFramework::Model("Modelos//Escritorio//Table.obj", "Modelos//Escritorio//Wood_texture.bmp", 1);
		Lamp = new EDXFramework::Model("Modelos//Lamp//LampS.obj", "Modelos//Lamp//Diffuse.bmp", 1);
		Extintor = new EDXFramework::Model("Modelos//extintor//extintor.obj", "Modelos//extintor//10285_Fire_Extinguisher_v2_difuse.bmp", 1);
		TCone = new EDXFramework::Model("Modelos//cone//TrafficCone.obj", "Modelos//cone//DiffuseHigh.bmp", 1);
		Fichero = new EDXFramework::Model("Modelos//Fichero//objDocuments.obj", "Modelos//Fichero//color.bmp", 1);
		WTable = new EDXFramework::Model("Modelos//desalto_bend//desalto_bend_in_obj.obj", "Modelos//desalto_bend//dcmap_desalto_bend_in_1.bmp", 1);
		Chair = new EDXFramework::Model("Modelos//OfficeCH//Office_chair.obj", "Modelos//OfficeCH//Office_chair_plastic_dif.bmp", 1);
		GasCan = new EDXFramework::Model("Modelos//Jug1_OBJ//Jug1.obj", "Modelos//Jug1_OBJ//Jug1_c.bmp", 1);
		Building = new EDXFramework::Model("Modelos//building//building.obj", "Modelos//building//concrete_building.bmp", 1);
		Tower = new EDXFramework::Model("Modelos//Tower//wooden watch tower2.obj", "Modelos//Tower//Wood_Tower_Col.bmp", 1);
		Gate = new EDXFramework::Model("Modelos//Gate//Gate.obj", "Modelos//Gate//PLATEOX2copy.bmp", 1);

		vector<thread> threads;
		Billboards(billBoard, hWnd);
		cameraInitialize();
	}
	void Billboards(Billboard *bills[], HWND hWnd) {
		//Aqui puedes crear algo util con un FOR quiza.
	}
	void render(HDC hDC) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		glLoadIdentity();
		GLfloat AmbInt[] = { 0.1, 0.1, 0.1, 1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbInt);
		py = terrain->Superficie(px, pz) * 4 + 6;

		cameraUpdate();
		////AMBIENTES:
		//Skydome
		glPushMatrix();
		glTranslatef(this->px, 8, this->pz);
		glRotatef(skyRotation, 0, 1, 0);
		skyDome->Draw();
		glPopMatrix();
		//Terreno
		glPushMatrix();
		glScalef(1, 4, 1);
		terrain->Draw();
		glPopMatrix();
		//Agua
		glPushMatrix();
		glTranslatef(0, 30.0f, 0);
		glScalef(2, 4, 2);
		lago->Draw();
		glPopMatrix();
		//Hands
		glPushMatrix();
		glTranslatef(this->px, this->py, this->pz);
		glRotatef(-this->angle, 0, 1, 0);
		glScalef(1, 1, 1);
		PlayerHands->Draw();
		glPopMatrix();
		//Building
		glPushMatrix();
		glTranslatef(0.0f, 37.0f, -200.0f);
		glScalef(0.45f, 0.45f, 0.45f);//Escalar
		Building->Draw();
		glPopMatrix();
		//Tower
		glPushMatrix();
		glTranslatef(145.0f, 75.6f, 295.0f);
		glScalef(1, 1, 1);//Escalar
		Tower->Draw();
		glPopMatrix();
		//Gate
		glPushMatrix();
		glTranslatef(-70.0f, 40.0f, 30.0f);
		glScalef(1, 1, 1);//Escalar
		Gate->Draw();
		glPopMatrix();

		////ENEMIGOS
		//Enemy1
		glPushMatrix();
		glTranslatef(0, 40.0f, -35.0f);
		glScalef(0.5, 0.5, 0.5);
		Enemy->Draw();
		glPopMatrix();
		//Enemy2
		glPushMatrix();
		glTranslatef(0, 40, -30.0f);
		glScalef(0.5, 0.5, 0.5);
		Enemy2->Draw();
		glPopMatrix();

		////OBJETOS:
		//KeyItem
		glPushMatrix();
		glTranslatef(0.0f, 40.0f, -15.0f);
		glScalef(0.8f, 0.8f, 0.8f);//Escalar
		KeyItem->Draw();
		glPopMatrix();
		//Car
		glPushMatrix();
		glTranslatef(0.0f, 40.f, 70.0f);
		glScalef(0.5f, 0.5f, 0.5f);//Escalar
		Car->Draw();
		glPopMatrix();
		//Laptop
		glPushMatrix();
		glTranslatef(0, 40, 40);
		glScalef(0.2f, 0.2f, 0.2f);//Escalar
		Laptop->Draw();
		glPopMatrix();
		//Telefono
		glPushMatrix();
		glTranslatef(0, 40.0f, 35.0f);
		glScalef(0.2f, 0.2f, 0.2f);//Escalar
		Telefono->Draw();
		glPopMatrix();
		//Escritorio
		glPushMatrix();
		glTranslatef(0, 40.0f, 30.0f);
		glScalef(2.2, 2.2, 2.2);//Escalar
		Escritorio->Draw();
		glPopMatrix();
		//Lampara
		glPushMatrix();
		glTranslatef(0, 40.0f, 25.0f);
		glScalef(0.3f, 0.3f, 0.3f);//Escalar
		Lamp->Draw();
		glPopMatrix();
		//Extintor
		glPushMatrix();
		glTranslatef(0, 40.0f, 20.0f);
		glScalef(0.4f, 0.4f, 0.4f);//Escalar
		Extintor->Draw();
		glPopMatrix();
		//Cone
		glPushMatrix();
		glTranslatef(0, 40.0f, 15.0f);
		glScalef(0.2f, 0.2f, 0.2f);//Escalar
		TCone->Draw();
		glPopMatrix();
		//Fichero
		glPushMatrix();
		glTranslatef(0, 40.0f, 10.0f);
		glScalef(2, 2, 2);//Escalar
		Fichero->Draw();
		glPopMatrix();
		//MesaTrabajo
		glPushMatrix();
		glTranslatef(0, 40.0f, 5.0f);
		glScalef(0.5, 0.5, 0.5);//Escalar
		WTable->Draw();
		glPopMatrix();
		//Chair
		glPushMatrix();
		glTranslatef(0, 40.0f, 0);
		glScalef(0.5, 0.5, 0.5);//Escalar
		Chair->Draw();
		glPopMatrix();
		//Gaso
		glPushMatrix();
		glTranslatef(0, 45.0f, -10.0f);
		glScalef(5, 5, 5);//Escalar
		GasCan->Draw();
		glPopMatrix();

		//glPushMatrix();
		//for (int i = 0; i < BILLSIZE; i++)
		//	//Aqui puede ir algo en especial, en tu carpeta de HEADER_FILES, el primer archivo es la respuesta.
		//	glPopMatrix();
		SwapBuffers(hDC);
	}
	~Scene() {
		delete PlayerHands;
		delete GasCan;
		delete skyDome;
		delete terrain;
		delete lago;
		delete Chair;
		delete WTable;
		delete Fichero;
		delete TCone;
		delete Extintor;
		delete Lamp;
		delete Escritorio;
		delete Telefono;
		delete Laptop;
		delete Tower;
		delete Building;
		delete Enemy;
		delete Enemy2;
		delete Car;
		delete KeyItem;
		delete Gate;
	}
};
#endif
