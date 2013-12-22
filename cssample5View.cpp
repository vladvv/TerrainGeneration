// cssample5View.cpp : implementation of the CCssample5View class
//

#include "stdafx.h"
#include "cssample5.h"
#include "Terrain.h"
#include "Vector.h"

#include "cssample5Doc.h"
#include "cssample5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define piover180 0.01745329251
#include "Number_Input.h"

Terrain land;


/////////////////////////////////////////////////////////////////////////////
// CCssample5View

IMPLEMENT_DYNCREATE(CCssample5View, CView)

BEGIN_MESSAGE_MAP(CCssample5View, CView)
	//{{AFX_MSG_MAP(CCssample5View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_AS4_SELECT_1, OnSelectControlPoint1)
	ON_COMMAND(ID_AS4_SELECT_2, OnSelectControlPoint2)
	ON_COMMAND(ID_AS4_SELECT_3, OnSelectControlPoint3)
	ON_COMMAND(ID_AS4_SELECT_4, OnSelectControlPoint4)
	ON_COMMAND(ID_AS4_X_DEC, OnXDec)
	ON_COMMAND(ID_AS4_X_INC, OnXInc)
	ON_COMMAND(ID_AS4_Y_DEC, OnYDec)
	ON_COMMAND(ID_AS4_Y_INC, OnYInc)
	ON_COMMAND(ID_AS4_Z_DEC, OnZDec)
	ON_COMMAND(ID_AS4_Z_INC, OnZInc)
	ON_COMMAND(ID_VIEW_TEXTURE_DISABLE, OnViewTextureDisable)
	ON_COMMAND(ID_VIEW_TEXTURE_ENABLE, OnViewTextureEnable)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_FAULTALGORITHM_1, &CCssample5View::OnFaultalgorithm1)
	ON_COMMAND(ID_VIEW_WIREFRAME32805, &CCssample5View::OnViewWireframe32805)
	ON_COMMAND(ID_VIEW_FILLED32806, &CCssample5View::OnViewFilled32806)
	ON_COMMAND(ID_FAULTALGORITHM_10, &CCssample5View::OnFaultalgorithm10)
	ON_COMMAND(ID_FAULTALGORITHM_100, &CCssample5View::OnFaultalgorithm100)
	ON_COMMAND(ID_FAULTALGORITHM_1000, &CCssample5View::OnFaultalgorithm1000)
	ON_COMMAND(ID_MESH_RESET, &CCssample5View::OnMeshReset)
	ON_COMMAND(ID_MESH_FLAT, &CCssample5View::OnMeshFlat)
	ON_COMMAND(ID_FAULTALGORITHM_STEP, &CCssample5View::OnFaultalgorithmStep)
	ON_COMMAND(ID_SMOOTH_1, &CCssample5View::OnSmooth1)
	ON_COMMAND(ID_SMOOTH_10, &CCssample5View::OnSmooth10)
	ON_COMMAND(ID_SMOOTH_100, &CCssample5View::OnSmooth100)
	ON_COMMAND(ID_SMOOTH_1000, &CCssample5View::OnSmooth1000)
	ON_COMMAND(ID_SMOOTH_SMOOTHINGFACTOR, &CCssample5View::OnSmoothSmoothingfactor)
	ON_COMMAND(ID_CIRCLES_1000, &CCssample5View::OnCircles1000)
	ON_COMMAND(ID_CIRCLES_100, &CCssample5View::OnCircles100)
	ON_COMMAND(ID_CIRCLES_10, &CCssample5View::OnCircles10)
	ON_COMMAND(ID_CIRCLES_1, &CCssample5View::OnCircles1)
	ON_COMMAND(ID_MESH_CLIP, &CCssample5View::OnMeshClip)
	ON_COMMAND(ID_COLOR_HEIGHTBASED, &CCssample5View::OnColorHeightbased)
	ON_COMMAND(ID_COLOR_OFF, &CCssample5View::OnColorOff)
	ON_COMMAND(ID_SHIFTMESH_, &CCssample5View::OnShiftmesh)
	ON_COMMAND(ID_SHIFTMESH_32827, &CCssample5View::OnShiftmesh32827)
	ON_COMMAND(ID_CLIPPING_ENABLED, &CCssample5View::OnClippingEnabled)
	ON_COMMAND(ID_CLIPPING_DISABLED, &CCssample5View::OnClippingDisabled)
	ON_COMMAND(ID_MESH_AVERAGE, &CCssample5View::OnMeshAverage)
	ON_COMMAND(ID_INCREMENTAL, &CCssample5View::OnIncremental)
	ON_COMMAND(ID_RANDOM, &CCssample5View::OnRandom)
	ON_COMMAND(ID_RANDOM_GENERATE, &CCssample5View::OnRandomGenerate)
	ON_COMMAND(ID_RANDOM_SETHEIGHT, &CCssample5View::OnRandomSetheight)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCssample5View construction/destruction
CCssample5View::CCssample5View()
{
	m_hDC=NULL;
	m_hRC=NULL;
	w=h=0; //width and height of view area
	control_point=0;
	x_step=0;
	y_step=0;
	z_step=0;

	color = 0;
	clipping_enabled = 0;

	RedSurface[0]= 1.0f; RedSurface[1]=0.0f; RedSurface[2]=0.0f; RedSurface[3]=1.0f;
	GreenSurface[0]= 0.0f; GreenSurface[1]=1.0f; GreenSurface[2]=0.0f; GreenSurface[3]=1.0f;
	BlueSurface[0]= 0.0f; BlueSurface[1]=0.0f; BlueSurface[2]=1.0f; BlueSurface[3]=1.0f;
	BlackSurface[0]= 0.0f; BlackSurface[1]=0.0f; BlackSurface[2]=0.0f; BlackSurface[3]=1.0f;


 

	LightPos.x=50;	LightPos.y=50; 	LightPos.z=50;
	WireFrame=1;
	rendering_mode=true; //smooth by default, otherwise flat
	CalcBezier();


	yaw = 0;
	pitch = 0;
	camera.x = 0;
	camera.y = -20;
	camera.z = 0;

	light.x = 0;
	light.y = 20;
	light.z = 0;
	wireframe = 0;

	
	
}

CCssample5View::~CCssample5View()
{
}

BOOL CCssample5View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCssample5View drawing

void CCssample5View::OnDraw(CDC* pDC)
{
	
	CCssample5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rcClient;
	GetClientRect(rcClient);
	
	w=rcClient.Width();
	h=rcClient.Height();

	wglMakeCurrent(m_hDC,m_hRC);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);		

	
	//glColor4f(1.0, 1.0, 1.0, 0.0);

	glViewport(0, 0, (int)(w/1.0), (int)(h/1.0));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w/(float)h, 1, 1024);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	0, 0, 0, 
				0, 0, 50, 
				0, 1, 0);
		
	glRotatef(pitch, 1.f, 0.f, 0.f);//pitch
	glRotatef(yaw, 0.f, 1.f, 0.f);//yaw
	glTranslatef(camera.x, camera.y, camera.z);


	//DrawXYZaxis();

	drawLand();
	drawLight();

	glDisable(GL_TEXTURE_2D);

	glFlush();



//	wglMakeCurrent(m_hDC,NULL);
	wglMakeCurrent(m_hDC,m_hRC);
    ::SwapBuffers(m_hDC);
}


void CCssample5View::drawLight(void)
{

}







void CCssample5View::drawLand(void)
{
	Vector polyNormals[land.x_dimension][land.y_dimension][2];




	for(int y = 0; y < land.y_dimension - 1; y++)
	{
		for(int x = 0; x < land.x_dimension - 1; x++)
		{
			Vector a = land.points[x][y];
			Vector b = land.points[x+1][y];
			Vector c = land.points[x+1][y+1];

				//perform clipping first, if needed
			if(clipping_enabled == 1)
			{
				if(a.y <= 0)
					a.y = 0;
				if(b.y <= 0)
					b.y = 0;
				if(c.y <= 0)
					c.y = 0;
			}



			Vector normal = Vector::CalcNormal(c,b,a);

			polyNormals[x][y][1] = normal;

			a = land.points[x][y];
			b = land.points[x+1][y+1];
			c = land.points[x][y+1];
			if(clipping_enabled == 1)
			{
				if(a.y <= 0)
					a.y = 0;
				if(b.y <= 0)
					b.y = 0;
				if(c.y <= 0)
					c.y = 0;
			}



			normal = Vector::CalcNormal(c,b,a);

			polyNormals[x][y][0] = normal;
		}
	}

	
	Vector vertexNormals[land.x_dimension][land.y_dimension];
	//calculate all vertex normals
	for(int y = 0; y < land.y_dimension; y++)
	{
		for(int x = 0; x < land.x_dimension; x++)
		{
			Vector sum = Vector(0,0,0);
			int count = 0;

			if(x > 0 && y > 0)
			{
				Vector face4 = polyNormals[x-1][y-1][1];
				Vector face5 = polyNormals[x-1][y-1][0];
				sum = Vector::add(sum, face4);
				sum = Vector::add(sum, face5);
				count += 2;
			}

			if(x < 19 && y < 19)
			{
				Vector face1 = polyNormals[x][y][0];
				Vector face2 = polyNormals[x][y][1];
				sum = Vector::add(sum, face1);
				sum = Vector::add(sum, face2);
				count += 2;
			}

			if(y > 0 && x < 19)
			{
				Vector face3 = polyNormals[x][y-1][0];
				sum = Vector::add(sum, face3);
				count++;
			}

			if(x > 0 && y < 19)
			{
				Vector face6 = polyNormals[x-1][y][0];
				sum = Vector::add(sum, face6);
				count++;
			}
			vertexNormals[x][y] = Vector::multiply(1.0/count, sum);
		}

	}

	//Do second run, drawing the vertices


	
	for(int y = 0; y < land.y_dimension -1 ; y++)
	{
		glBegin (GL_TRIANGLES);

		for(int x = 0; x < land.x_dimension - 1; x++)
		{		

			Vector a = land.points[x][y];
			Vector b = land.points[x][y+1];
			Vector c = land.points[x+1][y];
			Vector d = land.points[x+1][y+1];

			//perform clipping first, if needed
			if(clipping_enabled == 1)
			{
				if(a.y <= 0)
					a.y = 0;
				if(b.y <= 0)
					b.y = 0;
				if(c.y <= 0)
					c.y = 0;
				if(d.y <= 0)
					d.y = 0;
			}


			//if all points are at height = 0, make the piece water

			DetermineMaterial(a);
			//poly1
			glNormal3f(vertexNormals[x][y].x,vertexNormals[x][y].y,vertexNormals[x][y].z);
			glVertex3f(a.x, a.y, a.z);
			
			DetermineMaterial(b);
			glNormal3f(vertexNormals[x][y+1].x,vertexNormals[x][y+1].y,vertexNormals[x][y+1].z);
			glVertex3f(b.x, b.y, b.z);
			
			DetermineMaterial(c);
			glNormal3f(vertexNormals[x+1][y].x,vertexNormals[x+1][y].y,vertexNormals[x+1][y].z);
			glVertex3f(c.x, c.y, c.z);
			
			
			//poly2
			DetermineMaterial(c);
			glNormal3f(vertexNormals[x+1][y].x,vertexNormals[x+1][y].y,vertexNormals[x+1][y].z);
			glVertex3f(c.x, c.y, c.z);			

			DetermineMaterial(b);
			glNormal3f(vertexNormals[x][y+1].x,vertexNormals[x][y+1].y,vertexNormals[x][y+1].z);
			glVertex3f(b.x, b.y, b.z);

			DetermineMaterial(d);
			glNormal3f(vertexNormals[x+1][y+1].x,vertexNormals[x+1][y+1].y,vertexNormals[x+1][y+1].z);
			glVertex3f(d.x, d.y, d.z);

			 
		}
		glEnd();
	}





}

/////////////////////////////////////////////////////////////////////////////
// CCssample5View printing

BOOL CCssample5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CCssample5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}

void CCssample5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}

/////////////////////////////////////////////////////////////////////////////
// CCssample5View diagnostics

#ifdef _DEBUG
void CCssample5View::AssertValid() const
{
	CView::AssertValid();
}

void CCssample5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCssample5Doc* CCssample5View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCssample5Doc)));
	return (CCssample5Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCssample5View message handlers

int CCssample5View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	int nPixelFormat;				
	m_hDC = ::GetDC(m_hWnd);			

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	
		1,									
		PFD_DRAW_TO_WINDOW |			
		PFD_SUPPORT_OPENGL |			
		PFD_DOUBLEBUFFER,				
		PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0,					
		0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 
                PFD_MAIN_PLANE, 0, 0, 0, 0 
	};

    nPixelFormat = ::ChoosePixelFormat(m_hDC, &pfd);
    ::SetPixelFormat(m_hDC, nPixelFormat, &pfd);
    m_hRC = ::wglCreateContext(m_hDC);
    ::wglMakeCurrent(m_hDC,m_hRC);
    SetupGL();
    ::wglMakeCurrent(m_hDC,NULL);
	
	return 0;
}

void CCssample5View::OnDestroy() 
{
	CView::OnDestroy();
	// Clean up rendering context stuff
    ::wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd,m_hDC);	
}

void CCssample5View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
		
    ::wglMakeCurrent(m_hDC,m_hRC);
    SizeGL1(cx, cy);
    ::wglMakeCurrent(NULL,NULL);

}

// Setup GL view/projection matrices for window size.
void CCssample5View::SizeGL1(int w, int h)
{
        // Correct for zero dimensions.
        h = h ? h : 1;
        w = w ? w : 1;
 
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, w, 0, h);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glFlush();
}

void CCssample5View::SetupGL()
{
	SetupLightAndMaterial();
    glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0, .74, 1, 1);
}

void CCssample5View::SetupLightAndMaterial()
{
	glEnable(GL_LIGHTING);

	GLfloat LightAmbient[] =  { 0.2, 0.2, 0.2, 1.0};

	GLfloat LightDiffuse[] ={ .8, .8, .8, 1.0};
	GLfloat LightPos[] ={ light.x, light.y, light.z, 1};

	
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);	
	glLightfv(GL_LIGHT1, GL_POSITION, LightPos);



	glEnable(GL_LIGHT1); 

	

}

void CCssample5View::DrawXYZaxis()
{
	  //glColor4f(1.0, 0.0, 0.0, 0.0);
	  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RedSurface);
	  glBegin(GL_LINES);
		glVertex3f(-100, 0, 0);
		glVertex3f(100,  0, 0);
	  glEnd();

      //glColor4f(0.0, 1.0, 0.0, 0.0);
	  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GreenSurface);
      glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 100,  0);
	  glEnd();

      //glColor4f(0.0, 0.0, 1.0, 0.0);
	  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BlueSurface);
      glBegin(GL_LINES);
		glVertex3f(0, 0, -100);
		glVertex3f(0, 0,  100);
	  glEnd();
      //glColor4f(1.0, 1.0, 1.0, 0.0);
}

void CCssample5View::OnSelectControlPoint1() 
{

}

void CCssample5View::OnSelectControlPoint2() 
{

}

void CCssample5View::OnSelectControlPoint3() 
{

}

void CCssample5View::OnSelectControlPoint4() 
{

}

void CCssample5View::OnXDec() 
{

	InvalidateRect(NULL, FALSE);
}

void CCssample5View::OnXInc() 
{

	InvalidateRect(NULL, FALSE);
}

void CCssample5View::OnYDec() 
{

    InvalidateRect(NULL, FALSE);
}

void CCssample5View::OnYInc() 
{

	InvalidateRect(NULL, FALSE);
}

void CCssample5View::OnZDec() 
{

	InvalidateRect(NULL, FALSE);
}

void CCssample5View::OnZInc() 
{

	InvalidateRect(NULL, FALSE);
}

float CCssample5View::Bezier3(int j, float k)
{
return 0;
}

void CCssample5View::CalcBezier()
{

}

void CCssample5View::setAllNormals()
{
	//your implementation here
	//....
}

void CCssample5View::bezier_plane()
{

}

void CCssample5View::CalcNormal(Vector p1, Vector p2, Vector p3, float *n)
{
	//your implementation here
	//....
}

double CCssample5View::dotproduct(float *v1, double v2[])
{
	//your implementation here
	//....
	return 0;
}

void CCssample5View::OnViewFilled() 
{
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	InvalidateRect(NULL, FALSE);
}

void CCssample5View::OnViewWireframe() 
{

}

void CCssample5View::OnViewFlat() 
{
	//your implementation here
	//....	
}

void CCssample5View::OnViewSmooth() 
{
	//your implementation here
	//....
}


void CCssample5View::OnViewLightYdec() 
{
	//your implementation here
	//....
}

void CCssample5View::OnViewLightYinc() 
{
	//your implementation here
	//....	
}

BOOL CCssample5View::LoadImage(LPCTSTR fileName)
{
	HBITMAP hBmp = (HBITMAP) ::LoadImage (NULL,(LPCTSTR) fileName, 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE |LR_CREATEDIBSECTION);

	if (hBmp == NULL){
		AfxMessageBox("Error: unable to load bitmap file");
        return FALSE;
    }

    // Get bitmap info.
	::GetObject (hBmp, sizeof(texImage), &texImage);

    // Must be 24 bit
    if (texImage.bmBitsPixel != 24){
		AfxMessageBox("Error: bitmap must be 24 bit");
        return FALSE;
    }
        
    glBindTexture(GL_TEXTURE_2D, ImgName);
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, texImage.bmWidth, texImage.bmHeight, 
			GL_BGR_EXT, GL_UNSIGNED_BYTE, texImage.bmBits );

    return TRUE;
}

void CCssample5View::SetTexture()
{
	glDrawBuffer(GL_BACK);
	glGenTextures(1, &ImgName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	LoadImage("flower.bmp");
}

void CCssample5View::OnViewTextureDisable() 
{
	//your implementation here
	//....	
}

void CCssample5View::OnViewTextureEnable() 
{
	//your implementation here
	//....
}

void CCssample5View::OnViewPosDecz() 
{
	//your implementation here
	//....
}

void CCssample5View::OnViewPosIncz() 
{
	//your implementation here
	//....	
}



void CCssample5View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//TRACE("\nkeydown test: %c", nChar);

	switch(nChar) {
	case 37:   //right arrow
		yaw -= 5;
		break;
	case 38:  //up arrow
		slideCamera(-3);		
		break;
	case 39:  //left arrow
		yaw += 5;


		//OnCameraYawDown();
		break;
	case 40:  //down arrow
		slideCamera(3);	
		break;
	case 'W':
		pitch -= 5;
		//OnCameraPitchDown();
		break;
	case 'A':
		//OnCameraRollUp();
		break;
	case 'S':
		//OnCameraPitchUp();
		pitch += 5;
		break;
	}

	InvalidateRect(NULL, FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCssample5View::slideCamera(double amount)
{
	camera.x += (float)sin(-yaw * piover180) * cos(pitch * piover180) * amount;
	camera.y += (float)sin(pitch * piover180) * amount;
	camera.z += (float)cos(-yaw * piover180) * cos(pitch * piover180) *amount;
}





void CCssample5View::OnFaultalgorithm1()
{
	land.Terrain::Generate(Terrain::FAULT, 1);	
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnViewWireframe32805()
{
	color = 0;
	wireframe = 1;
	glColor4f(0, 1.0, 0, 0.0);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glShadeModel(GL_FLAT);
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnViewFilled32806()
{
	wireframe = 0;
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glShadeModel(GL_SMOOTH);
	InvalidateRect(NULL, FALSE);
}

void CCssample5View::OnMeshFlat()
{
	wireframe = 0;
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glShadeModel(GL_FLAT);
	InvalidateRect(NULL, FALSE);
}



void CCssample5View::OnFaultalgorithm10()
{
	land.Terrain::Generate(Terrain::FAULT, 10);	
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnFaultalgorithm100()
{
	land.Terrain::Generate(Terrain::FAULT, 100);	
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnFaultalgorithm1000()
{
	land.Terrain::Generate(Terrain::FAULT, 1000);	
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnMeshReset()
{
	land.reset();
	InvalidateRect(NULL, FALSE);
}




void CCssample5View::OnFaultalgorithmStep()
{
		Number_Input inp;

	CString input1 = "";
	if(inp.DoModal() == IDOK) {
		input1 = inp.entered;
	}

	TRACE("New Smoothing Factor: %s", input1);

	double temp = atof(input1);
	land.fault_step = temp;

}



void CCssample5View::OnSmooth1()
{
	land.Terrain::Generate(Terrain::SMOOTH, 1);	
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnSmooth10()
{
	land.Terrain::Generate(Terrain::SMOOTH, 10);	
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnSmooth100()
{
	land.Terrain::Generate(Terrain::SMOOTH, 100);
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnSmooth1000()
{
	land.Terrain::Generate(Terrain::SMOOTH, 1000);
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnSmoothSmoothingfactor()
{
	Number_Input inp;

	CString input1 = "";
	if(inp.DoModal() == IDOK) {
		input1 = inp.entered;
	}

	TRACE("New Smoothing Factor: %s", input1);

	double temp = atof(input1);
	land.smooth_factor = temp;

}


void CCssample5View::OnCircles1000()
{
	land.Terrain::Generate(Terrain::CIRCLES, 1000);
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnCircles100()
{
	land.Terrain::Generate(Terrain::CIRCLES, 100);
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnCircles10()
{
	land.Terrain::Generate(Terrain::CIRCLES, 10);
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnCircles1()
{
	land.Terrain::Generate(Terrain::CIRCLES, 1);
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnMeshClip()
{

	land.Terrain::Clip(0);
	InvalidateRect(NULL, FALSE);
}

void CCssample5View::SetMaterial(Material material)
{

	GLfloat mat_specular[] = { .7, .7, .7, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat mat_diffuse[] = {.9, .9, .9, 1 };


	//GL_DIFFUSE
	if(wireframe == 1)
	{
		mat_diffuse[0] = .5;
		mat_diffuse[1] = 0;
		mat_diffuse[2] = 0;
		mat_diffuse[3] = 1;

	} else if(color == 1){
		switch (material)
		{
		case LAND:
			mat_diffuse[0] = .35;
			mat_diffuse[1] = .30;
			mat_diffuse[2] = .25;
			mat_diffuse[3] = 1;
			break;

		case WATER:
			mat_diffuse[0] = 0;
			mat_diffuse[1] = .98;
			mat_diffuse[2] = .98;
			mat_diffuse[3] = 1;
			break;

		case ICE:
			mat_diffuse[0] = .8;
			mat_diffuse[1] = 1;
			mat_diffuse[2] = 1;
			mat_diffuse[3] = 1;
			break;
		case SAND:
			mat_diffuse[0] = .88;
			mat_diffuse[1] = .66;
			mat_diffuse[2] = .37;
			mat_diffuse[3] = 1;
			break;
		case GRASS:
			mat_diffuse[0] = .01;
			mat_diffuse[1] = .55;
			mat_diffuse[2] = .054;
			mat_diffuse[3] = 1;
			break;

		}
	}




	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	


}


void CCssample5View::OnColorHeightbased()
{
	color = 1;
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnColorOff()
{
	color = 0;
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnShiftmesh()
{
	land.Terrain::Shift(5);
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnShiftmesh32827()
{
	land.Terrain::Shift(-5);
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnClippingEnabled()
{
	clipping_enabled = 1;
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnClippingDisabled()
{
	clipping_enabled = 0;
	InvalidateRect(NULL, FALSE);
}


	#define WATER_LEVEL 0
	#define SAND_LEVEL 3
	#define GRASS_LEVEL 6
	#define LAND_LEVEL 40
	#define ICE_LEVEL 0


void CCssample5View::DetermineMaterial(Vector a, Vector b, Vector c)
{
	if(a.y <= WATER_LEVEL && b.y <= WATER_LEVEL && c.y <= WATER_LEVEL)
		SetMaterial(WATER);
	else if(a.y <= SAND_LEVEL && b.y <= SAND_LEVEL && c.y <= SAND_LEVEL)
		SetMaterial(SAND);
	else if(a.y <= GRASS_LEVEL && b.y <= GRASS_LEVEL && c.y <= GRASS_LEVEL)
		SetMaterial(GRASS);
	else if(a.y <= LAND_LEVEL && b.y <= LAND_LEVEL && c.y <= LAND_LEVEL)
		SetMaterial(LAND);
	else
		SetMaterial(ICE);
}

void CCssample5View::DetermineMaterial(Vector a)
{
	if(a.y <= WATER_LEVEL)
		SetMaterial(WATER);
	else if(a.y <= SAND_LEVEL)
		SetMaterial(SAND);
	else if(a.y <= GRASS_LEVEL)
		SetMaterial(GRASS);
	else if(a.y <= LAND_LEVEL)
		SetMaterial(LAND);
	else
		SetMaterial(ICE);
}

void CCssample5View::OnMeshAverage()
{
	land.AverageHeight();
	InvalidateRect(NULL, FALSE);

}


void CCssample5View::OnIncremental()
{
	land.Terrain::IncrementalGenerate();
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnRandom()
{
	
}


void CCssample5View::OnRandomGenerate()
{
	land.Terrain::RandomGenerate();
	InvalidateRect(NULL, FALSE);
}


void CCssample5View::OnRandomSetheight()
{
	Number_Input inp;

	CString input1 = "";
	if(inp.DoModal() == IDOK) {
		input1 = inp.entered;
	}

	TRACE("New Smoothing Factor: %s", input1);

	double temp = atof(input1);
	land.random_height = temp;
}
