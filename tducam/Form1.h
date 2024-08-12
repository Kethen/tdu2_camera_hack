#pragma once
#include "memory.h"
#include "d3d9.h"
#include "d3dx9.h"

float camspeed = 0.008f;
float fovspeed = 0.15f;
float TORAD = (3.14f / 180.0f);
float tirdata[32]={0};
float limitmov = 0.12;
float limityaw = 1.0;
float limitpitch = 0.5;
float limitpitchh = 0.3;
double angsens = 0.005986328125;// * (1.0+(float)trackBar1->Value*0.1);
double movesens = 0.00002103515625;// * (1.0+(float)trackBar2->Value*0.1);
bool check1 = false;
bool check2 = false;
bool check3 = false;
bool check4 = false;

FILE* fl = NULL;
D3DXMATRIX tMat;
D3DXMATRIX mMat;
D3DXMATRIX rMat;
bool kd = false;
bool mkd = false;
bool mm = false;
DWORD off = 0;
long mptr = 0;
long cptr = 0;
long optr = 0;

long smptr = 0;
long scptr = 0;
long soptr = 0;
bool sthread = false;

DWORD ticks=0;
DWORD tickskey=0;

long off_fov = 0x5e4;
struct guidata
{
	int sl1;
	int sl2;
	char tir;
	char hcam;
	char tlcam;
	char ext1;
	char lcam;
	char ext2;
	char ext3;
	char ext4;
};
guidata gd={0};

struct camerad
{
    float PosOffsetX;
    float PosOffsetY;
    float PosOffsetZ;
    float OriOffsetX;
    float OriOffsetY;
    float OriOffsetZ;
};


struct cameradn
{
	float nfov;
	float npitch;
	float nyaw;
	float ext1;
};




float fov = 0;
float sfov = 0;
float mfov = 0;
float m_pitch = 0;
float m_yaw = 0;
BYTE sl[4]={0};
BYTE slr[4]={9,0,4,0};


BYTE mover[0x30] ={0};
BYTE mmover[0x30]={0};
bool didmover = false;

camerad tircamera={0};
camerad tircamerar={0};
camerad modcamera[10000][25]={0};
cameradn modcameran[10000][25]={0};
camerad origcamera={0};
bool origloaded={0};
long viewid = 0;
long oviewid = 0;
long carid = 0;
long ocarid = 0;


long tbar1=0;
long tbar2=0;




namespace tducam {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	using namespace System::Runtime::InteropServices;
	using namespace System::Threading;

    //track ir imports
    [DllImport("tir.dll")]
    extern "C" int start(int hwnd, Int16 profile);
    [DllImport("tir.dll")]
    extern "C" int shutdown();
    [DllImport("tir.dll")]
    extern "C" int poll(float * mX, float * mY);
    [DllImport("tir.dll")]
    extern "C" int getarray(float * outArr);

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:

		Thread^ oThread;




		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Timer^  timer1;

	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	private: System::Windows::Forms::Label^  label2;


	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Timer^  timer2;

	private: System::ComponentModel::IContainer^  components;
	protected: 
	
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// linkLabel1
			// 
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->Location = System::Drawing::Point(322, 309);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(86, 13);
			this->linkLabel1->TabIndex = 1;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"ToCAEDIT.COM";
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Form1::linkLabel1_LinkClicked);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 309);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(37, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Status";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->checkBox4);
			this->groupBox1->Controls->Add(this->checkBox3);
			this->groupBox1->Controls->Add(this->checkBox2);
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->trackBar2);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->trackBar1);
			this->groupBox1->Location = System::Drawing::Point(280, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(128, 213);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"TrackIR";
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Checked = true;
			this->checkBox4->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox4->Location = System::Drawing::Point(6, 138);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(74, 17);
			this->checkBox4->TabIndex = 14;
			this->checkBox4->Text = L"Use Limits";
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Checked = true;
			this->checkBox3->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox3->Location = System::Drawing::Point(6, 184);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(117, 17);
			this->checkBox3->TabIndex = 13;
			this->checkBox3->Text = L"Disable HeadMove";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox3_CheckedChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Checked = true;
			this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox2->Location = System::Drawing::Point(6, 161);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(113, 17);
			this->checkBox2->TabIndex = 12;
			this->checkBox2->Text = L"Disable SteerLook";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(6, 115);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(87, 17);
			this->checkBox1->TabIndex = 11;
			this->checkBox1->Text = L"Use TrackIR";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// label5
			// 
			this->label5->Location = System::Drawing::Point(3, 96);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(118, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Translate: 0";
			this->label5->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(6, 64);
			this->trackBar2->Maximum = 40;
			this->trackBar2->Minimum = -10;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(115, 45);
			this->trackBar2->TabIndex = 9;
			this->trackBar2->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->trackBar2->Value = 1;
			this->trackBar2->Scroll += gcnew System::EventHandler(this, &Form1::trackBar2_Scroll);
			// 
			// label4
			// 
			this->label4->Location = System::Drawing::Point(3, 45);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(118, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Rotate: 0";
			this->label4->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(6, 13);
			this->trackBar1->Maximum = 40;
			this->trackBar1->Minimum = -10;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(115, 45);
			this->trackBar1->TabIndex = 7;
			this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->trackBar1->Value = 1;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &Form1::trackBar1_Scroll);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Location = System::Drawing::Point(16, 231);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(258, 75);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"TrackIR Data";
			this->groupBox2->Enter += gcnew System::EventHandler(this, &Form1::groupBox2_Enter);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(118, 16);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 13);
			this->label6->TabIndex = 5;
			this->label6->Text = L"label6";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(16, 16);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"label3";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label1);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox3->Location = System::Drawing::Point(16, 12);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(258, 213);
			this->groupBox3->TabIndex = 9;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"HotKeys";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(223, 182);
			this->label1->TabIndex = 1;
			this->label1->Text = resources->GetString(L"label1.Text");
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->label7);
			this->groupBox4->Location = System::Drawing::Point(280, 231);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(127, 75);
			this->groupBox4->TabIndex = 10;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Game Info";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(15, 16);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(0, 13);
			this->label7->TabIndex = 0;
			// 
			// timer2
			// 
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(421, 340);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->linkLabel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"TDU2 Camera Hack v1.4";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Form1::Form1_FormClosed);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void SaveData()
		{
			fl = fopen("tdu2cam.sav", "wb");
			if (fl != NULL)
			{
				gd.sl1 = trackBar1->Value;
				gd.sl2 = trackBar2->Value;
				gd.tir = checkBox1->Checked;
				gd.lcam = checkBox2->Checked;
				gd.hcam = checkBox3->Checked;
				gd.tlcam = checkBox4->Checked;
				fwrite(&gd,sizeof(guidata),1,fl);
				fwrite(&modcamera,sizeof(camerad),10000*25,fl);
				fwrite(&modcameran,sizeof(cameradn),10000*25,fl);
				fclose(fl);
			}
		}
		void LoadData()
		{
			fl = fopen("tdu2cam.sav", "rb");
			if (fl != NULL)
			{
				fread(&gd,sizeof(guidata),1,fl);
				fread(&modcamera,sizeof(camerad),10000*25,fl);
				fread(&modcameran,sizeof(cameradn),10000*25,fl);
				fclose(fl);
			}
				trackBar1->Value = gd.sl1;
				trackBar2->Value = gd.sl2;
				checkBox1->Checked = gd.tir;
				checkBox2->Checked = gd.lcam;
				checkBox3->Checked = gd.hcam;
				checkBox4->Checked = gd.tlcam;
				label5->Text = "Translate: " + trackBar2->Value.ToString();
				label4->Text = "Rotate: " + trackBar1->Value.ToString();
		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				linkLabel1->Links->RemoveAt(0);
				linkLabel1->Links->Add(0, linkLabel1->Text->Length, "http://tocaedit.com");
				////
				LoadData();
				try{start(0, 0xC1D);}catch(...){}
				//StartWaiter();

				oThread = gcnew Thread(gcnew ThreadStart(this,&Form1::tirthread));
				oThread->Start();

    //SetPriorityClass (
     //               GetCurrentProcess(),
      //              ABOVE_NORMAL_PRIORITY_CLASS
       //              );

				//newThread = gcnew Thread(gcnew ThreadStart(this->tirthread ));
				//newThread->Start();
				
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

				tbar1 = trackBar1->Value;
				tbar2 = trackBar2->Value;

				check1 = checkBox1->Checked;
				check2 = checkBox2->Checked;
				check3 = checkBox3->Checked;
				check4 = checkBox4->Checked;
				//read tirdata
				 //low priority stuff
				if(GetTickCount()-ticks > 100)
				{
					ticks = GetTickCount();
			 		angsens = 0.005986328125 * (1.0+(float)tbar1*0.1);
					movesens = 0.00002103515625 * (1.0+(float)tbar2*0.1);
 					if(checkBox1->Checked == true)
					{
						label3->Text = "X: " + tircamera.PosOffsetX.ToString() + "\n" + "Y: " + tircamera.PosOffsetY.ToString() + "\n" +  "Z: " + tircamera.PosOffsetZ.ToString();
						label6->Text = "RX: " + tircamera.OriOffsetX.ToString() + "\n" + "RY: " + tircamera.OriOffsetY.ToString() + "\n" +  "RZ: " + tircamera.OriOffsetZ.ToString();
					}
					else
					{
						label3->Text = "X: 0\nY: 0\nZ: 0" ;
						label6->Text = "RX: 0\nRY: 0\nRZ: 0" ;

					}


					GetID("Eden Applications");
					if(hWin) 
						label2->Text = "Status: Game found!";
					else{
						label2->Text = "Status: Game not found!";
						label7->Text = "N/A";
						return;
					}

					label2->Text = "Status: Scanning for offset...";
					
					off = FutureScan();
					if(off) 
						label2->Text = "Status: Offset found!";
					else{
						label2->Text = "Status: Offset not found!";
						return;
					}


					//get pointers
					mptr = GetLong(off);
					mptr = GetLong(mptr);
					cptr = GetLong(mptr + 0x420);
					


					//get current camera
					oviewid = viewid;
					ocarid = carid;
					viewid = GetLong(cptr + 0x2e8);
					//carid = GetLong(cptr + 0x2e4);
					carid = GetLong(mptr + 0x94);

					//if(viewid == 20 || viewid == 21) return;

					label7->Text = "Ptr: " + cptr.ToString() + "\nCarID: " + carid.ToString() + "\nViewID: " + viewid.ToString();
					

					//5a4 = fov
					//38c = look left/right
					//390 = look up/down
					//2c0 = disable look (bit 3)
					//F7C = camera id
					//560 = camera movements
					//398 car id 2?

					//return;

					if((viewid!=oviewid || carid!=ocarid))
					{


						//set last cam back to default
						if(optr && (oviewid > 18 && oviewid < 25)){
							SetByte(optr+ off_fov, (char)(fov));
							SetByte(optr+ off_fov+1, (char)(sfov));
							SetBytes(optr+0x560, mover, 0x30);
							SetBytes(optr+0x300, sl,0x4);
							if(oviewid == 20 || oviewid == 21)
							{
								SetFloat(optr+0x3a4,origcamera.PosOffsetZ  );
							}
							else
							{
								SetFloat(optr+0x540,origcamera.PosOffsetX);
								SetFloat(optr+0x544,origcamera.PosOffsetY);
								SetFloat(optr+0x548,origcamera.PosOffsetZ);
								SetFloat(optr+0x550,origcamera.OriOffsetX);
								SetFloat(optr+0x554,origcamera.OriOffsetY);
								SetFloat(optr+0x558,origcamera.OriOffsetZ);
							}
						}
						if(viewid > 25)return;
						if(carid > 10000)return;
						optr = cptr;
						//get current cam data

						if(viewid == 20 || viewid == 21)
						{
							origcamera.PosOffsetZ = GetFloat(cptr+0x3a4);
						}
						else
						{
							
								origcamera.PosOffsetX=GetFloat(cptr+0x540);
								origcamera.PosOffsetY=GetFloat(cptr+0x544);
								origcamera.PosOffsetZ=GetFloat(cptr+0x548);
								origcamera.OriOffsetX=GetFloat(cptr+0x550);
								origcamera.OriOffsetY=GetFloat(cptr+0x554);
								origcamera.OriOffsetZ=GetFloat(cptr+0x558);
							//
						}


						//cam changed, load initial values
						GetBytes(cptr+0x560,mover,0x30);
						fov=(float)GetByte(cptr+ off_fov);
						sfov=(float)GetByte(cptr+ off_fov+1);
						GetBytes(cptr+0x300,sl,0x4);
						didmover = false;
						sthread = false; //un-stop thread

					}
				}

				if(viewid > 25)return;
				if(carid > 10000)return;

				//medium priority stuff
				if(GetTickCount()-tickskey > 10)
				{
					tickskey = GetTickCount();
					if(GetAsyncKeyState(VK_ADD))
					{
						modcamera[carid][viewid].PosOffsetZ+=camspeed;
						modcamera[carid][viewid].OriOffsetZ+=camspeed;
					}

					if(GetAsyncKeyState(VK_SUBTRACT))
					{
						modcamera[carid][viewid].PosOffsetZ-=camspeed;
						modcamera[carid][viewid].OriOffsetZ-=camspeed;
					}

					if(GetAsyncKeyState(VK_NUMPAD4))
					{
						modcamera[carid][viewid].PosOffsetX+=camspeed;
						modcamera[carid][viewid].OriOffsetX+=camspeed;
					}

					if(GetAsyncKeyState(VK_NUMPAD6))
					{
						modcamera[carid][viewid].PosOffsetX-=camspeed;
						modcamera[carid][viewid].OriOffsetX-=camspeed;
					}

					if(GetAsyncKeyState(VK_NUMPAD8))
					{
						modcamera[carid][viewid].PosOffsetY+=camspeed;
						modcamera[carid][viewid].OriOffsetY+=camspeed;
					}

					if(GetAsyncKeyState(VK_NUMPAD2))
					{
						modcamera[carid][viewid].PosOffsetY-=camspeed;
						modcamera[carid][viewid].OriOffsetY-=camspeed;
					}
					if(GetAsyncKeyState(VK_MULTIPLY))
					{
						modcameran[carid][viewid].nfov+=fovspeed;
					}
					if(GetAsyncKeyState(VK_DIVIDE))
					{
						modcameran[carid][viewid].nfov-=fovspeed;
					}
					
					if(GetAsyncKeyState(VK_NUMPAD0))
					{
						modcameran[carid][viewid].nyaw+=camspeed;
					}
					if(GetAsyncKeyState(VK_DECIMAL))
					{
						modcameran[carid][viewid].nyaw-=camspeed;
					}
					if(GetAsyncKeyState(VK_NUMPAD9))
					{
						modcameran[carid][viewid].npitch-=camspeed;
					}
					if(GetAsyncKeyState(VK_NUMPAD3))
					{
						modcameran[carid][viewid].npitch+=camspeed;
					}

					if(GetAsyncKeyState(VK_NUMPAD5))
					{
						modcamera[carid][viewid].PosOffsetX=0;
						modcamera[carid][viewid].PosOffsetY=0;
						modcamera[carid][viewid].PosOffsetZ=0;
						modcamera[carid][viewid].OriOffsetX=0;
						modcamera[carid][viewid].OriOffsetY=0;
						modcamera[carid][viewid].OriOffsetZ=0;
						modcameran[carid][viewid].nfov=0;
						modcameran[carid][viewid].npitch=0;
						modcameran[carid][viewid].nyaw=0;
					}

					if(GetAsyncKeyState(VK_NUMPAD7))
					{
						if(kd == false)
						{
							for(int i = 0;i<10000;i++)
							{
								if(i!=carid){
									modcamera[i][viewid].PosOffsetX=modcamera[carid][viewid].PosOffsetX;
									modcamera[i][viewid].PosOffsetY=modcamera[carid][viewid].PosOffsetY;
									modcamera[i][viewid].PosOffsetZ=modcamera[carid][viewid].PosOffsetZ;
									modcamera[i][viewid].OriOffsetX=modcamera[carid][viewid].OriOffsetX;
									modcamera[i][viewid].OriOffsetY=modcamera[carid][viewid].OriOffsetY;
									modcamera[i][viewid].OriOffsetZ=modcamera[carid][viewid].OriOffsetZ;
									modcameran[i][viewid].nfov=modcameran[carid][viewid].nfov;
									modcameran[i][viewid].npitch=modcameran[carid][viewid].npitch;
									modcameran[i][viewid].nyaw=modcameran[carid][viewid].nyaw;
								}
							}
							kd=true;
						}
					}else{
						kd=false;
					}	
				}
			
			 }
	private: System::Void linkLabel1_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				ProcessStartInfo ^ sInfo = gcnew ProcessStartInfo(e->Link->LinkData->ToString());
				Process::Start(sInfo);
			 }
private: System::Void Form1_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {

			 if(oThread!=nullptr)oThread->Abort();
			 if(hWin) {
 					//set last cam back to default
					if(optr && (oviewid > 18 && oviewid < 25)){
						SetByte(optr+ off_fov, (char)(fov));
						SetByte(optr+ off_fov+1, (char)(sfov));
						SetBytes(optr+0x560, mover, 0x30);
						SetBytes(optr+0x300, sl,0x4);
						if(oviewid == 20 || oviewid == 21)
						{
							SetFloat(optr+0x3a4,origcamera.PosOffsetZ  );
						}
						else
						{
							SetFloat(optr+0x540,origcamera.PosOffsetX);
							SetFloat(optr+0x544,origcamera.PosOffsetY);
							SetFloat(optr+0x548,origcamera.PosOffsetZ);
							SetFloat(optr+0x550,origcamera.OriOffsetX);
							SetFloat(optr+0x554,origcamera.OriOffsetY);
							SetFloat(optr+0x558,origcamera.OriOffsetZ);
						}
					}
			 }

				try{shutdown();}catch(...){}
				SaveData();
		 }
private: System::Void trackBar2_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 label5->Text = "Translate: " + trackBar2->Value.ToString();

		 }
private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 label4->Text = "Rotate: " + trackBar1->Value.ToString();
		 }
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void groupBox2_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void checkBox3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 didmover = false;
		 }
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {

		 }
void tirthread()
		{
			while(true)
			{
				//Get TrackIR Data

 				if(check1 == true)
				{

					try {
						getarray(tirdata);
					}
				
					catch (...) {}

					//getarray(tirdata);
					tircamera.OriOffsetX = - tirdata[3] * (float)angsens * TORAD;
					tircamera.OriOffsetY = -tirdata[4] * (float)angsens * TORAD;
					tircamera.OriOffsetZ = -tirdata[2] * (float)angsens * TORAD;

					tircamera.PosOffsetX = tirdata[5] * (float)movesens;
					tircamera.PosOffsetY = tirdata[6] * (float)movesens;
					tircamera.PosOffsetZ = -tirdata[7] * (float)movesens;
					//writetircamstruct();


					
					if(check4 == true)
					{
						if(tircamera.OriOffsetX>limitpitchh)tircamera.OriOffsetX=limitpitchh;
						if(tircamera.OriOffsetX<-limitpitch)tircamera.OriOffsetX=-limitpitch;
						if(tircamera.OriOffsetY>limityaw)tircamera.OriOffsetY=limityaw;
						if(tircamera.OriOffsetY<-limityaw)tircamera.OriOffsetY=-limityaw;
						if(tircamera.OriOffsetZ>limityaw)tircamera.OriOffsetZ=limityaw;
						if(tircamera.OriOffsetZ<-limityaw)tircamera.OriOffsetZ=-limityaw;

						if(tircamera.PosOffsetX>limitmov)tircamera.PosOffsetX=limitmov;
						if(tircamera.PosOffsetX<-limitmov)tircamera.PosOffsetX=-limitmov;
						if(tircamera.PosOffsetY>limitmov)tircamera.PosOffsetY=limitmov;
						if(tircamera.PosOffsetY<-limitmov)tircamera.PosOffsetY=-limitmov;
						if(tircamera.PosOffsetZ>limitmov)tircamera.PosOffsetZ=limitmov;
						if(tircamera.PosOffsetZ<-limitmov)tircamera.PosOffsetZ=-limitmov;
					}
				}


				//Write Data

				OpenProcessSafe();
				smptr = GetLongSafe(off);
				smptr = GetLongSafe(smptr);
				scptr = GetLongSafe(smptr + 0x420);

				if(soptr != scptr) sthread = true;

				soptr = scptr;

				if(sthread == true)goto end;


				if(viewid == 20 || viewid == 21)
				{
					SetFloatSafe(cptr+0x3a4, origcamera.PosOffsetZ+modcamera[carid][viewid].PosOffsetZ);
					SetByteSafe(cptr+ off_fov, (char)(fov+modcameran[carid][viewid].nfov));
					SetByteSafe(cptr+ off_fov+1, (char)(sfov+modcameran[carid][viewid].nfov));
				}
				else
				{
					if(viewid < 25 && viewid > 19)
					{
						if(check2 == true && (viewid == 23 || viewid == 24)){
							SetBytesSafe(cptr+0x300, slr,4);
						}else{
							SetBytesSafe(cptr+0x300, sl,4);
						}

						if(check3 == true && (viewid == 23 || viewid == 24)){
							if(didmover==false){
								SetBytesSafe(cptr+0x560, mmover, 0x30);
								didmover = true;
							}
						}else{
							if(didmover==false){
								SetBytesSafe(cptr+0x560, mover, 0x30);
								didmover = true;
							}
						}

						if(check1 == true && (viewid == 23 || viewid == 24))
						{
							D3DXMatrixRotationYawPitchRoll(&rMat,modcameran[carid][viewid].npitch+-tircamera.OriOffsetX,0,modcameran[carid][viewid].nyaw+-tircamera.OriOffsetY);
							rMat._41 = tircamera.PosOffsetX+modcamera[carid][viewid].PosOffsetX+origcamera.PosOffsetX;
							rMat._42 = tircamera.PosOffsetY+modcamera[carid][viewid].PosOffsetY+origcamera.PosOffsetY;
							rMat._43 = tircamera.PosOffsetZ+modcamera[carid][viewid].PosOffsetZ+origcamera.PosOffsetZ;
							rMat._44 = 1.0;
						}
						else
						{
							
							D3DXMatrixRotationYawPitchRoll(&rMat,modcameran[carid][viewid].npitch,0,modcameran[carid][viewid].nyaw);
							rMat._41 = modcamera[carid][viewid].PosOffsetX+origcamera.PosOffsetX;
							rMat._42 = modcamera[carid][viewid].PosOffsetY+origcamera.PosOffsetY;
							rMat._43 = modcamera[carid][viewid].PosOffsetZ+origcamera.PosOffsetZ;
							rMat._44 = 1.0;

						}
		 				SetBytesSafe(cptr+0x540, (BYTE*)&rMat._41, 16);
						rMat._41+=rMat._12;
						rMat._42+=rMat._13;
						rMat._43+=rMat._11;
						SetBytesSafe(cptr+0x550,(BYTE*)&rMat._41, 16);

						SetByteSafe(cptr+ off_fov, (char)(fov+modcameran[carid][viewid].nfov));
						SetByteSafe(cptr+ off_fov+1, (char)(sfov+modcameran[carid][viewid].nfov));
					}
				}
end:
				CloseProcessSafe();
				System::Threading::Thread::Sleep(1);
			}

		}

};
}
		
	

