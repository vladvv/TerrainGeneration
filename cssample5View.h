// cssample5View.h : interface of the CCssample5View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSsample5VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_)
#define AFX_CSsample5VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector.h"



class CCssample5View : public CView
{
protected: // create from serialization only
	CCssample5View();
	DECLARE_DYNCREATE(CCssample5View)

// Attributes
public:
	CCssample5Doc* GetDocument();

	enum Material {WATER, LAND, ICE, SAND, GRASS};

// Operations
public:
	
	int m_GLPixelIndex;	
	HDC m_hDC;
	HGLRC m_hRC;

	GLdouble m_ytheta;
	GLdouble m_xtheta;
	CPoint m_LDownPos;
	BOOL m_LButtonDown;

	int w, h;
	int angle, rangle;
	int control_point;

	int clipping_enabled;


	Vector camera;
	Vector light;

	float pitch;
	float yaw;

	Vector step;
	Vector u, v, n;
	int x_step;
	int y_step;
	int z_step;
	float normal[40][40][3];
	float vnormal[21][21][3];
	int color;
	int wireframe;

	void CCssample5View::SetMaterial(Material material);
	void CCssample5View::DetermineMaterial(Vector a);

	GLfloat RedSurface[4];
	GLfloat GreenSurface[4];
	GLfloat YellowSurface[4];
	GLfloat WhiteSurface[4];
	GLfloat BlueSurface[4];
	GLfloat BlackSurface[4];
	
	// Setup GL view/projection matrices for window size.
    void SizeGL1(int w, int h);
    // Setup default params (lighting, etc...) for GL.
    void SetupGL();
    // Render scene using OpenGL.
    void DrawCylinder(int base_radius, int top_radius, int height);
	void drawLight(void);
	void DrawXYZaxis();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCssample5View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void setAllNormals();
	void SetTexture();
	GLuint ImgName;
	BITMAP texImage;
	BOOL LoadImage(LPCTSTR fileName);
	Vector Camera;
	Vector LightPos;
	void CalcBezier();
	BOOL rendering_mode;
	double dotproduct(float* v1, double v2[]);
	int WireFrame;
	void SetupLightAndMaterial(void);
	void CalcNormal(Vector p1, Vector p2, Vector p3, float *n);
	void bezier_plane(void);
	float Bezier3(int j, float k);
	virtual ~CCssample5View();
	void slideCamera(double amount);
	

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCssample5View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelectControlPoint1();
	afx_msg void OnSelectControlPoint2();
	afx_msg void OnSelectControlPoint3();
	afx_msg void OnSelectControlPoint4();
	afx_msg void OnXDec();
	afx_msg void OnXInc();
	afx_msg void OnYDec();
	afx_msg void OnYInc();
	afx_msg void OnZDec();
	afx_msg void OnZInc();
	afx_msg void OnViewFilled();
	afx_msg void OnViewWireframe();
	afx_msg void OnViewFlat();
	afx_msg void OnViewSmooth();
	afx_msg void OnViewLightYdec();
	afx_msg void OnViewLightYinc();
	afx_msg void OnViewTextureDisable();
	afx_msg void OnViewTextureEnable();
	afx_msg void OnViewPosDecz();
	afx_msg void OnViewPosIncz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void drawLand(void);
	afx_msg void OnFaultalgorithm1();
	afx_msg void OnViewWireframe32805();
	afx_msg void OnViewFilled32806();
	afx_msg void OnFaultalgorithm10();
	afx_msg void OnFaultalgorithm100();
	afx_msg void OnFaultalgorithm1000();
	afx_msg void OnMeshReset();
	afx_msg void OnMeshFlat();
	afx_msg void OnFaultalgorithmStep();
	afx_msg void OnSmooth1();
	afx_msg void OnSmooth10();
	afx_msg void OnSmooth100();
	afx_msg void OnSmooth1000();
	afx_msg void OnSmoothSmoothingfactor();
	afx_msg void OnCircles1000();
	afx_msg void OnCircles100();
	afx_msg void OnCircles10();
	afx_msg void OnCircles1();
	afx_msg void OnMeshClip();
	afx_msg void OnColorHeightbased();
	afx_msg void OnColorOff();
	afx_msg void OnShiftmesh();
	afx_msg void OnShiftmesh32827();
	afx_msg void OnClippingEnabled();
	afx_msg void OnClippingDisabled();
	void DetermineMaterial(Vector a, Vector b, Vector c);
	afx_msg void OnMeshAverage();
	afx_msg void OnIncremental();
	afx_msg void OnRandom();
	afx_msg void OnRandomGenerate();
	afx_msg void OnRandomSetheight();
};

#ifndef _DEBUG  // debug version in cssample5View.cpp
inline CCssample5Doc* CCssample5View::GetDocument()
   { return (CCssample5Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSsample5VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_)
