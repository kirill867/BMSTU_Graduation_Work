// *.cpp: ������� ���� �������.

#include "Form1.h"
#include <cmath>

using namespace kernel;

[STAThreadAttribute]

int main(array<System::String ^> ^args)
{
	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	Application::Run(gcnew Form1());
	return 0;
}

//====     ���������    ======================

#define cell 56	//������ ������ � ��������
#define cx 50	//������ ������ � ������
#define ct 1	//������ ������ � ��������
#define cv 10	//������ ������ � ����/�������

#define lf 30	//�� ������ ���� �� ��� �
#define bm 30	//�� ������� ���� �� ��� �

#define M_PI  3.14159265358979323846
#define gg 9.81	//��������� ���������� �������
#define rr 1.29	//��������� �������
#define cc 0.15	//����������� �������� �������������
#define ee 0.01	//�������� ��������

/*
//====     �������� ���������� �����   (�� Form1.h) ����� ������� ���������� � ����� ������ ���������� ���������� =====


		int modGraf; //����� ������� 1-����������  2-��������
		int iMax; //���� � ����.������� ������
		bool tochn; //������ ����� ��������
		bool prost; //������ ��������� ��������
		int Wpic,Hpic; //������ � ������ �������
		int NN,nn; //���������� ����� (�������������� � �����)
		System::String ^byY,^byX; //������� ����� ���� ���������
		double bb; //����.������������������ ���� �������� �������������
		double RR; //������ ����
		double mm; //����� ����
		double HH; //������� ������������ ������ � ������ �������� (���� ��� ���� ������ �����)
		int H0; //������� ������� �� ��� ��
		double VV,Vx,Vy; //��������� �������� � �� �������� �� ���
		double TP,YMAX,XMAX; //�����, ������ � ��������� ����������

		//������� ������ �������� ��� ������� ����
		double *pVV,*pVx,*pVy; //��������� �� ������� ���������
		double *pX,*pY,*pt; //��������� �� ������� ���������, ������ � �������
		double *ayx,*byx,*cyx; //��������� �� ������� ����. ������ �� ���������
		double *ayt,*byt,*cyt; //��������� �� ������� ����. ������ �� �������

		double AA; //��������� ���� ��������
		double ro; //��������� ��������� ����
		double h,H; //��� �������������� ��������� � �����������
*/




Void Form1::Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 //��������� ��������� ���������� ��� �������� �����
			 modGraf=1;	
			 HH=0;	H0=0;	//������� ������ - ��� ������� ������ ���� ���������
			 tochn=false; //������ ����� �� ��������
			 prost=false; //������ ��������� �� ��������
			 radioButton1_CheckedChanged(sender, e);
			 
}





Void Form1::PrepareData(void){
		//������ ������ � �����
	VV=(double)numericUpDown1->Value;
	AA=(double)numericUpDown2->Value;
	ro=(double)numericUpDown3->Value;
	RR=(double)numericUpDown4->Value;
	h=(double)numericUpDown5->Value;
	HH=(double)numericUpDown6->Value;

		//���������� ��������� ������ (���������� �����)
	bb=0.5*cc*rr*M_PI*RR*RR;
	mm=4*ro*M_PI*RR*RR*RR/3.0;
	Vx=VV*cos(AA*M_PI/180);
	Vy=VV*sin(AA*M_PI/180);
	NN=(int)(2.9*VV*sin(AA*M_PI/180)/gg/h);//����������� ��� �������� (� ��������� �������������)

	
	delete[] pVx;//������������ ������ ���������� ��������  
	delete[] pVy;
	delete[] pVV;
	delete[] pY;
	delete[] pX;
	delete[] pt;
	delete[] ayx;
	delete[] byx;
	delete[] cyx;
	delete[] ayt;
	delete[] byt;
	delete[] cyt;
	

	pVx=new double[NN];	//������������ ��������� ������ ��� �������
	pVy=new double[NN];
	pVV=new double[NN];
	pY=new double[NN];
	pX=new double[NN];
	pt=new double[NN];
	ayx=new double[NN];	
	byx=new double[NN];
	cyx=new double[NN];
	ayt=new double[NN];
	byt=new double[NN];
	cyt=new double[NN];


	

}

// ������� ���������� �������������� �������� ��������
double Form1::fvx( double vy, double vx )  
{ double answ= -bb*vx*sqrt(vx*vx+vy*vy) / mm;
  return answ;
}
// ������� ���������� ������������ �������� ��������
double Form1::fvy( double vy, double vx )  
{ double answ= -bb*vy*sqrt(vx*vx+vy*vy) / mm - gg;
  return answ;  
}

Void Form1::FullArrs(void){
	double k1,k2,k3,k4,l1,l2,l3,l4,_h;

	pY[0]=HH; pX[0]=0; pt[0]=0;  //��������� �������� ���������� pY[0] ����� ���� ������� �� ���� (��� ������ �����)
	pVx[0]=Vx; pVy[0]=Vy; pVV[0]=VV;	
	bool vzbool=true;//�����
	int i=1;

		//������ �� ������ � ���������� ��������
	while( (pY[i-1]>-0.00001 || vzbool) && i<NN )
	{	if(i>1) _h=h; else _h=h/2; //������ ��� � ��� ���� ������, ����� ��������� ������ ������ ������� ���������������
		pt[i] =pt[i-1]+_h;
		k1 =  _h * fvx( pVy[i-1], pVx[i-1]);				l1 =  _h * fvy( pVy[i-1], pVx[i-1]); 
		k2 =  _h * fvx( pVy[i-1]+l1/2, pVx[i-1]+k1/2 );		l2 =  _h * fvy( pVy[i-1]+l1/2, pVx[i-1]+k1/2 );
		k3 =  _h * fvx( pVy[i-1]+l2/2, pVx[i-1]+k2/2 );		l3 =  _h * fvy( pVy[i-1]+l2/2, pVx[i-1]+k2/2 );
		k4 =  _h * fvx( pVy[i-1]+l3, pVx[i-1]+k3 );			l4 =  _h * fvy( pVy[i-1]+l3, pVx[i-1]+k3 );
		
		

		pVx[i]=pVx[i-1] + (k1+2*k2+2*k3+k4)/6;			pVy[i]=pVy[i-1] + (l1+2*l2+2*l3+l4)/6;		
		pVV[i] = sqrt( pVx[i]*pVx[i] + pVy[i]*pVy[i] ); //�������� ������� �������� �� ��������
		double tmx=pVx[i];	//��� ��������� ��� �������
		double tmy=pVy[i];
		double tm =pVV[i]; //�������� ������� �������� �� ��������
		


		pY[i]=pY[i-1]+pVy[i]*h; pX[i]=pX[i-1]+pVx[i]*h; 
		if(pY[i]>pY[i-1]) iMax=i; //���������� ������ ���� � ������������ �������
		else vzbool=false;//�������
		
		double tx=pX[i];	//��� ��������� ��� �������
		double ty=pY[i];
		
		i++;
	}
	nn=i-1; //���������� �������� �����
		
		double tmx1=pVx[i-1];	//��� ��������� ��� �������
		double tmy1=pVy[i-1];
		double tm1 =pVV[i-1]; //�������� ������� �������� �� ��������
		double tx1=pX[i-1];
		double ty1=pY[i-1];		
		double tt1=pt[i-1];
			
}

Void Form1::FullInterpolacArrs(void){
	double x1,dx,x3,t1,dt,t3,y1,y2,y3;
		ayx[0] =0;		byx[0] =0;		cyx[0] =0;		
		ayt[0] =0;		byt[0] =0;		cyt[0] =0;

		//������ ����.������������ � ������ � �������
	for( int i=1; i<nn; i++ )
	{	x1=pX[i-1]; x3=pX[i+1]; dx=(x3-x1)/2; if(dx<0.5) dx=0.5;
		t1=pt[i-1]; t3=pt[i+1]; dt=(t3-t1)/2; if(dt<0.5) dt=0.5;
		y1=pY[i-1]; y2=pY[i]; y3=pY[i+1];
		//����.��� ������� ������ �� ��������� 
		ayx[i] =y2;
		byx[i] =(y3-y1)/2/dx;					double xmb=byx[i];
		cyx[i] =(y3-2*y2+y1)/2/dx/dx;			double xmc=cyx[i];
		//����.��� ������� ������ �� ������� 
		ayt[i] =y2;
		byt[i] =(y3-y1)/2/dt;				double tmb=byt[i];
		cyt[i] =(y3-2*y2+y1)/2/dt/dt;		double tmc=cyt[i];
		//
	}	
	TochnResult();
}

Void Form1::TochnResult(void){
	double R1,R2,D,a,b,c; //��� ���������� ��� ������� ���������

	XMAX=pX[nn-1];  //���� [nn-1]
	a=ayx[nn-1];b=byx[nn-1];c=cyx[nn-1];
	D=b*b-4*a*c;  if(D>=0){
	R1=(-b+sqrt(D))/2/c; //������� �������.���������
	R2=(-b-sqrt(D))/2/c; //������� �������.���������
	if(R1>R2) XMAX=XMAX+R1; else XMAX=XMAX+R2;
	}
	
	pX[nn]=XMAX;  pY[nn]=0;//����������� ��������� ����

	label7->Text=Convert::ToString((int)(1000*XMAX)/1000.0); //��������� ���������� �� 3 �����

	TP=pt[nn-1];//���� [nn-1]
	a=ayt[nn-1];b=byt[nn-1];c=cyt[nn-1];
	D=b*b-4*a*c;  if(D>=0){
	R1=(-b+sqrt(D))/2/c; //������� �������.���������
	R2=(-b-sqrt(D))/2/c; //������� �������.���������
	if(R1>R2) TP=TP+R1; else TP=TP+R2;
	}
	//pt[nn]=loc; �� ����������� ��������� ����, ����� �� ���������� ������� ���������

	label9->Text=Convert::ToString((int)(1000*TP)/1000.0); //����� ������ ���������� �� 3 �����

	YMAX=pY[iMax]; 
	label11->Text=Convert::ToString((int)(1000*YMAX)/1000.0); //������������ ������ ������ ���������� �� 3 �����
}

Void Form1::ShowResult(void){
	
	label7->Text=Convert::ToString((int)(1000*XMAX)/1000.0); //��������� ���������� �� 3 �����

	label9->Text=Convert::ToString((int)(1000*TP)/1000.0); //����� ������ ���������� �� 3 �����

	label11->Text=Convert::ToString((int)(1000*YMAX)/1000.0); //������������ ������ ������ ���������� �� 3 �����
}

Void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e){
	PrepareData();
	FullArrs(); 
	FullInterpolacArrs(); 
	tochn=true; //������ ��������
	
	pictureBox1->Refresh();	//������ ����������
	ShowResult();
	//MessageBox::Show("����� �������� ������ '�� ������ �����-�����'...","����� ����:",	
	//					MessageBoxButtons::OK, MessageBoxIcon::Information);

}

Void Form1::button2_Click(System::Object^  sender, System::EventArgs^  e){
	PrepareData();
	prost=true; tochn=false;
	pictureBox1->Refresh();	//������ ����������
	//MessageBox::Show("����� �������� ���������� ������ '�� ������ ��������'...","����� ����:",	
	//					MessageBoxButtons::OK, MessageBoxIcon::Information);
}

Void Form1::Prosto(System::Windows::Forms::PaintEventArgs^  e){
	double Y=HH,t=0,X=0,Ymax=HH;	
	float x1,y1,x2,y2,kx=(float)cell/cx,sme=(float)(H0*cell/cx);
	bool vzbool=true;//�����

	int n, i=1;

		//������ �� ���������� ������ � ����� � ������
	while( Y>-0.00001 || vzbool)
	{	t =i*h/10;
		X=Vx*t; 
		Y=X*sin(AA*M_PI/180)/cos(AA*M_PI/180)-(gg*X*X/2/Vx/Vx)+HH;
		
		if(i==1) {x1=lf+kx*(float)X; y1=Hpic-bm-sme-kx*(float)Y;}
		else 
		{	
			x2=lf+kx*(float)X;
			y2=Hpic-bm-sme-kx*(float)Y;
			e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::Gray, 1), x1, y1, x2, y2);
			x1=x2;
			y1=y2;
		}
		if(Y>Ymax) Ymax=Y; //����������  ������������ �������	
		else vzbool=false;//�������
		i++;
	}
	n=i-1; //���������� �������� �����

	//����� �����������
	label7->Text=Convert::ToString((int)(1000*X)/1000.0); //��������� ���������� �� 3 �����
	label9->Text=Convert::ToString((int)(1000*t)/1000.0); //����� ������ ���������� �� 3 �����
	label11->Text=Convert::ToString((int)(1000*Ymax)/1000.0); //������������ ������ ������ ���������� �� 3 �����
	
}


//================================  ���������� ������������ ������� �������  ===============================

Void Form1::ShowAxis1(System::Windows::Forms::PaintEventArgs^  e) {
	System::Int32 fstr;	//������� ������� ����� ���� ���������
	System::Drawing::Font ^objFont = gcnew System::Drawing::Font("Arial", 9);
	System::Drawing::Brush ^objBrush = System::Drawing::Brushes::Black;

	//�������� �������� ��� ��
	if(HH<0)H0=((int)(-HH/cx)+1)*cx ;
	else H0=0;

	for(int i=0;i<20;i++)
	{
		e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::LightBlue, 1), lf+cell*i, Hpic-bm, lf+cell*i, 3);
		if(i>0) 
		{	
			fstr=i*cx; ;
			e->Graphics->DrawString(Convert::ToString(fstr), objFont, objBrush, (float)lf+cell*i-12, (float)Hpic-25);
		}

		e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::LightBlue, 1), lf, Hpic-bm-cell*i, Wpic-3, Hpic-bm-cell*i);
		fstr=i*cx-H0;
		e->Graphics->DrawString(Convert::ToString(fstr), objFont, objBrush, 4, (float)Hpic-bm-cell*i-15);

	}
	e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::Black, 2), lf, Hpic-10, lf, 1);
	e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::Black, 2), 10, Hpic-bm-(H0*cell/cx), Wpic-1, Hpic-bm-(H0*cell/cx));

	//������� ���������� �� ����	
	objFont = gcnew System::Drawing::Font("Arial", 14);
	e->Graphics->DrawString(byY, objFont, objBrush, 37, 7);
	e->Graphics->DrawString(byX, objFont, objBrush, (float)Wpic-25, (float)Hpic-55-(H0*cell/cx));

}

//----------------------------------------------

Void Form1::ShowAxis2(System::Windows::Forms::PaintEventArgs^  e) {
	System::Int32 fstr;	//������� ������� ����� ���� ���������
	System::Drawing::Font ^objFont = gcnew System::Drawing::Font("Arial", 9);
	System::Drawing::Brush ^objBrush = System::Drawing::Brushes::Black;

	
	for(int i=0;i<20;i++)
	{
		e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::LightBlue, 1), lf+cell*i, Hpic-bm, lf+cell*i, 3);
		if(i>0) 
		{	
			fstr=i*ct;
			e->Graphics->DrawString(Convert::ToString(fstr), objFont, objBrush, (float)lf+cell*i-12, (float)Hpic-25);
		}
		e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::LightBlue, 1), lf, Hpic-bm-cell*i, Wpic-3, Hpic-bm-cell*i);
		if(i>0) 
		{	
			fstr=i*cv;
			e->Graphics->DrawString(Convert::ToString(fstr), objFont, objBrush, 4, (float)Hpic-bm-cell*i-10);
		}
	}
	e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::Black, 2), lf, Hpic-10, lf, 1);
	e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::Black, 2), 10, Hpic-bm, Wpic-1, Hpic-bm);

	//������� ���������� �� ����	
	objFont = gcnew System::Drawing::Font("Arial", 14);
	e->Graphics->DrawString(byY, objFont, objBrush, 37, 7);
	e->Graphics->DrawString(byX, objFont, objBrush, (float)Wpic-25, (float)Hpic-55);
}

//================================  ���������� �������  ==========================================


Void Form1::ShowTochn(System::Windows::Forms::PaintEventArgs^  e) {	
	float kx,ky,sme=(float)(H0*cell/cx);
	float x1,y1,x2,y2;
	for(int i=0;i<nn;i++)
	{	if(modGraf==1)
		{	kx=(float)cell/cx;
			x1=lf+kx*(float)pX[i];
			y1=Hpic-bm-sme-kx*(float)pY[i];
			x2=lf+kx*(float)pX[i+1];
			y2=Hpic-bm-sme-kx*(float)pY[i+1];
		e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::Red, 2), x1, y1, x2, y2);
		}
		else if(modGraf==2)
		{	kx=(float)cell/ct; ky=(float)cell/cv;
			x1=lf+kx*(float)pt[i];
			y1=Hpic-bm-ky*(float)pVV[i];
			x2=lf+kx*(float)pt[i+1];
			y2=Hpic-bm-ky*(float)pVV[i+1];
		e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::Blue, 3), x1, y1, x2, y2);
		}
		else if(modGraf==3)
		{	kx=(float)cell/ct; ky=(float)cell/cv;
			x1=lf+kx*(float)pt[i];
			y1=Hpic-bm-ky*abs((float)pVy[i]);
			x2=lf+kx*(float)pt[i+1];
			y2=Hpic-bm-ky*abs((float)pVy[i+1]);
		e->Graphics->DrawLine(gcnew Pen(System::Drawing::Color::Green, 3), x1, y1, x2, y2);
		}
	}	
}


//=================================================================================


Void Form1::radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e){	
	if(radioButton1->Checked) {byY="H"; byX="S"; modGraf=1; pictureBox1->Refresh();}
	
		 }

Void Form1::radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e){	
	if(radioButton2->Checked) {byY="V"; byX="t"; modGraf=2; pictureBox1->Refresh();}

		 }

Void Form1::radioButton3_CheckedChanged(System::Object^  sender, System::EventArgs^  e){	
	if(radioButton3->Checked)  {byY="V"; byX="t"; modGraf=3; pictureBox1->Refresh();}

		 }


//==============  ����������� ����� � ������� ==============================
Void Form1::pictureBox1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e){
	if(modGraf==1)
		ShowAxis1(e); //��� ��� �������	
	else
		ShowAxis2(e); //��� ��� �������	
	if(prost && modGraf==1) Prosto(e);
	if(tochn) ShowTochn(e);		 
}

Void Form1::Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	ResizePicture()	;	 
		 pictureBox1->Refresh();
}
//=================================================================================


//=================   ��������� �������� �����   ============================
Void Form1::Form1_ResizeBegin(System::Object^  sender, System::EventArgs^  e) {
	Form1_ResizeEnd(sender,   e);			
}

Void Form1::Form1_ResizeEnd(System::Object^  sender, System::EventArgs^  e) {
	ResizePicture()	;
		 pictureBox1->Refresh();
}



Void Form1::Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
	ResizePicture()	;	 
		 pictureBox1->Refresh();
			// MessageBox::Show("Resize...","����� ����:",	
			//			MessageBoxButtons::OK, MessageBoxIcon::Information);
}

Void Form1::ResizePicture(void){
	//���������������, ������ ������� ������� ��� ��������� �������� �����
	this->groupBox3->Width=this->Width-212;
	this->groupBox3->Height=this->Height-71;
	this->pictureBox1->Width=this->groupBox3->Width-12;
	this->pictureBox1->Height=this->groupBox3->Height-60;
	Wpic=pictureBox1->Width; Hpic=pictureBox1->Height;
}


//=================================================================================