#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

// --- Стили оформления (Flat Design) ---
ref class Theme {
public:
    static Color BgColor = Color::FromArgb(245, 247, 250);
    static Color CardColor = Color::White;
    static Color PrimaryColor = Color::FromArgb(13, 110, 253);
    static Color SuccessColor = Color::FromArgb(25, 135, 84);
    static Color TextColor = Color::FromArgb(33, 37, 41);
    static Color BorderColor = Color::FromArgb(222, 226, 230);

    static void ApplyGridStyle(DataGridView^ grid) {
        grid->BackgroundColor = CardColor;
        grid->BorderStyle = BorderStyle::None;
        grid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
        grid->GridColor = BorderColor;
        grid->EnableHeadersVisualStyles = false;
        grid->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
        grid->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(248, 249, 250);
        grid->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
        grid->ColumnHeadersHeight = 40;
        grid->DefaultCellStyle->SelectionBackColor = Color::FromArgb(226, 238, 255);
        grid->DefaultCellStyle->SelectionForeColor = TextColor;
        grid->DefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 10);
        grid->RowTemplate->Height = 35;
        grid->RowHeadersVisible = false;
        grid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
    }

    static void ApplyButtonStyle(Button^ btn, Color bgColor) {
        btn->FlatStyle = FlatStyle::Flat;
        btn->FlatAppearance->BorderSize = 0;
        btn->BackColor = bgColor;
        btn->ForeColor = Color::White;
        btn->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
        btn->Cursor = Cursors::Hand;
    }
};

// --- 1. Форма Администратора ---
public ref class AdminForm : public Form {
private:
    DataGridView^ gridUsers, ^ gridSchedule;
    TextBox^ txtFio, ^ txtSubject, ^ txtRoom, ^ txtTime;
    ComboBox^ cbRole, ^ cbDay;
    int nextUserId = 3;

public:
    AdminForm() {
        this->Text = L"EduSystem - Административная панель";
        this->Size = System::Drawing::Size(900, 650);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = Theme::BgColor;

        Panel^ header = gcnew Panel(); header->BackColor = Theme::CardColor; header->Height = 60; header->Dock = DockStyle::Top;
        Label^ lblTitle = gcnew Label(); lblTitle->Text = L"Панель управления деканата"; lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
        lblTitle->Location = Point(20, 15); lblTitle->AutoSize = true; header->Controls->Add(lblTitle);

        TabControl^ tabs = gcnew TabControl(); tabs->Dock = DockStyle::Fill; tabs->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);

        TabPage^ pageUsers = gcnew TabPage(L"База пользователей"); pageUsers->BackColor = Theme::BgColor;
        Panel^ uCard = gcnew Panel(); uCard->BackColor = Theme::CardColor; uCard->Location = Point(20, 20); uCard->Size = System::Drawing::Size(840, 500);

        Label^ l1 = gcnew Label(); l1->Text = L"ФИО:"; l1->Location = Point(20, 20); l1->AutoSize = true;
        txtFio = gcnew TextBox(); txtFio->Location = Point(20, 40); txtFio->Width = 200;
        Label^ l2 = gcnew Label(); l2->Text = L"Роль:"; l2->Location = Point(240, 20); l2->AutoSize = true;
        cbRole = gcnew ComboBox(); cbRole->Items->AddRange(gcnew array<Object^>{L"Студент", L"Преподаватель"}); cbRole->SelectedIndex = 0;
        cbRole->Location = Point(240, 40); cbRole->Width = 150; cbRole->DropDownStyle = ComboBoxStyle::DropDownList;
        Button^ btnAddU = gcnew Button(); btnAddU->Text = L"Добавить"; btnAddU->Location = Point(410, 38); btnAddU->Size = System::Drawing::Size(120, 30);
        Theme::ApplyButtonStyle(btnAddU, Theme::SuccessColor); btnAddU->Click += gcnew EventHandler(this, &AdminForm::OnAddUser);
        gridUsers = gcnew DataGridView(); gridUsers->Location = Point(20, 90); gridUsers->Size = System::Drawing::Size(800, 380);
        gridUsers->ColumnCount = 3; gridUsers->Columns[0]->Name = L"ID"; gridUsers->Columns[1]->Name = L"ФИО"; gridUsers->Columns[2]->Name = L"Роль";
        gridUsers->Columns[1]->Width = 400; gridUsers->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
        Theme::ApplyGridStyle(gridUsers); gridUsers->Rows->Add(L"#001", L"Вяльцев М.А.", L"Студент");
        uCard->Controls->Add(l1); uCard->Controls->Add(txtFio); uCard->Controls->Add(l2); uCard->Controls->Add(cbRole); uCard->Controls->Add(btnAddU); uCard->Controls->Add(gridUsers);
        pageUsers->Controls->Add(uCard);

        TabPage^ pageSched = gcnew TabPage(L"Составление расписания"); pageSched->BackColor = Theme::BgColor;
        Panel^ sCard = gcnew Panel(); sCard->BackColor = Theme::CardColor; sCard->Location = Point(20, 20); sCard->Size = System::Drawing::Size(840, 500);
        txtSubject = gcnew TextBox(); txtSubject->Location = Point(20, 40); txtSubject->Width = 180;
        cbDay = gcnew ComboBox(); cbDay->Items->AddRange(gcnew array<Object^>{L"Пн", L"Вт", L"Ср", L"Чт", L"Пт", L"Сб"}); cbDay->SelectedIndex = 0;
        cbDay->Location = Point(210, 40); cbDay->Width = 80; cbDay->DropDownStyle = ComboBoxStyle::DropDownList;
        txtTime = gcnew TextBox(); txtTime->Text = L"08:30"; txtTime->Location = Point(300, 40); txtTime->Width = 80;
        txtRoom = gcnew TextBox(); txtRoom->Location = Point(390, 40); txtRoom->Width = 60;
        Button^ btnAddS = gcnew Button(); btnAddS->Text = L"В сетку"; btnAddS->Location = Point(470, 38); btnAddS->Size = System::Drawing::Size(120, 30);
        Theme::ApplyButtonStyle(btnAddS, Theme::PrimaryColor); btnAddS->Click += gcnew EventHandler(this, &AdminForm::OnAddSchedule);
        gridSchedule = gcnew DataGridView(); gridSchedule->Location = Point(20, 90); gridSchedule->Size = System::Drawing::Size(800, 380);
        gridSchedule->ColumnCount = 4; gridSchedule->Columns[0]->Name = L"Дисциплина"; gridSchedule->Columns[1]->Name = L"День";
        gridSchedule->Columns[2]->Name = L"Время"; gridSchedule->Columns[3]->Name = L"Ауд.";
        gridSchedule->Columns[0]->Width = 350; Theme::ApplyGridStyle(gridSchedule);
        gridSchedule->Rows->Add(L"Проектирование ИС", L"Пн", L"10:10", L"402");
        sCard->Controls->Add(txtSubject); sCard->Controls->Add(cbDay); sCard->Controls->Add(txtTime); sCard->Controls->Add(txtRoom);
        sCard->Controls->Add(btnAddS); sCard->Controls->Add(gridSchedule);
        pageSched->Controls->Add(sCard);

        tabs->TabPages->Add(pageUsers); tabs->TabPages->Add(pageSched);
        this->Controls->Add(tabs); this->Controls->Add(header);
    }
    void OnAddUser(Object^ sender, EventArgs^ e) { if (String::IsNullOrWhiteSpace(txtFio->Text)) return; gridUsers->Rows->Add(L"#00" + (++nextUserId).ToString(), txtFio->Text, cbRole->Text); txtFio->Clear(); }
    void OnAddSchedule(Object^ sender, EventArgs^ e) { if (String::IsNullOrWhiteSpace(txtSubject->Text)) return; gridSchedule->Rows->Add(txtSubject->Text, cbDay->Text, txtTime->Text, txtRoom->Text); txtSubject->Clear(); txtRoom->Clear(); }
};

// --- 2. Форма Студента (Расписание + Оценки + Справки) ---
public ref class StudentForm : public Form {
private:
    ComboBox^ cbDocType;
public:
    StudentForm() {
        this->Text = L"EduSystem - Личный кабинет Студента";
        this->Size = System::Drawing::Size(920, 800);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = Theme::BgColor;

        Panel^ header = gcnew Panel(); header->BackColor = Theme::CardColor; header->Height = 60; header->Dock = DockStyle::Top;
        Label^ lblMain = gcnew Label(); lblMain->Text = L"Электронный кабинет студента"; lblMain->Font = gcnew System::Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
        lblMain->Location = Point(20, 15); lblMain->AutoSize = true; header->Controls->Add(lblMain);

        Panel^ cardSched = gcnew Panel(); cardSched->BackColor = Theme::CardColor; cardSched->Location = Point(25, 80); cardSched->Size = System::Drawing::Size(850, 200);
        DataGridView^ gS = gcnew DataGridView(); gS->Location = Point(20, 45); gS->Size = System::Drawing::Size(810, 140);
        gS->ColumnCount = 4; gS->Columns[0]->Name = L"Дисциплина"; gS->Columns[1]->Name = L"День"; gS->Columns[2]->Name = L"Время"; gS->Columns[3]->Name = L"Ауд.";
        gS->Columns[0]->Width = 350; Theme::ApplyGridStyle(gS);
        gS->Rows->Add(L"Базы данных", L"Пн", L"08:30", L"305");
        cardSched->Controls->Add(gS);

        Panel^ cardGrades = gcnew Panel(); cardGrades->BackColor = Theme::CardColor; cardGrades->Location = Point(25, 300); cardGrades->Size = System::Drawing::Size(850, 200);
        DataGridView^ gG = gcnew DataGridView(); gG->Location = Point(20, 45); gG->Size = System::Drawing::Size(810, 140);
        gG->ColumnCount = 3; gG->Columns[0]->Name = L"Дисциплина"; gG->Columns[1]->Name = L"Тип контроля"; gG->Columns[2]->Name = L"Оценка";
        gG->Columns[0]->Width = 350; Theme::ApplyGridStyle(gG);
        gG->Rows->Add(L"Дискретная математика", L"Экзамен", L"Отлично (5)");
        cardGrades->Controls->Add(gG);

        Panel^ cardDocs = gcnew Panel(); cardDocs->BackColor = Theme::CardColor; cardDocs->Location = Point(25, 520); cardDocs->Size = System::Drawing::Size(850, 160);
        cbDocType = gcnew ComboBox(); cbDocType->Items->AddRange(gcnew array<Object^>{L"Справка об обучении (в военкомат)", L"Справка-вызов на сессию"});
        cbDocType->SelectedIndex = 0; cbDocType->Location = Point(20, 80); cbDocType->Width = 400; cbDocType->DropDownStyle = ComboBoxStyle::DropDownList;
        Button^ btnOrder = gcnew Button(); btnOrder->Text = L"Заказать документ"; btnOrder->Location = Point(440, 78); btnOrder->Size = System::Drawing::Size(200, 32);
        Theme::ApplyButtonStyle(btnOrder, Theme::PrimaryColor); btnOrder->Click += gcnew EventHandler(this, &StudentForm::OnOrderClick);
        cardDocs->Controls->Add(cbDocType); cardDocs->Controls->Add(btnOrder);

        this->Controls->Add(cardDocs); this->Controls->Add(cardGrades); this->Controls->Add(cardSched); this->Controls->Add(header);
    }
    void OnOrderClick(Object^ sender, EventArgs^ e) { MessageBox::Show(L"Заявка принята!"); }
};

// --- 3. Форма Авторизации (ИСПРАВЛЕНО) ---
public ref class LoginForm : public Form {
private:
    TextBox^ txtLogin, ^ txtPass;
public:
    LoginForm() {
        this->Text = L"Вход в EduSystem"; this->Size = System::Drawing::Size(350, 400); this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = Theme::BgColor; this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog; this->MaximizeBox = false;

        Panel^ card = gcnew Panel(); card->BackColor = Theme::CardColor; card->Size = System::Drawing::Size(280, 280); card->Location = Point(27, 40);

        Label^ title = gcnew Label(); title->Text = L"Авторизация"; title->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, FontStyle::Bold); title->Location = Point(50, 20); title->AutoSize = true;

        Label^ lblL = gcnew Label(); lblL->Text = L"Логин:"; lblL->Location = Point(30, 80); lblL->AutoSize = true;
        txtLogin = gcnew TextBox(); txtLogin->Location = Point(30, 100); txtLogin->Width = 220;

        Label^ lblP = gcnew Label(); lblP->Text = L"Пароль:"; lblP->Location = Point(30, 140); lblP->AutoSize = true;
        txtPass = gcnew TextBox(); txtPass->Location = Point(30, 160); txtPass->Width = 220; txtPass->PasswordChar = '*';

        Button^ btn = gcnew Button(); btn->Text = L"Войти"; btn->Location = Point(30, 210); btn->Size = System::Drawing::Size(220, 35);
        Theme::ApplyButtonStyle(btn, Theme::PrimaryColor); btn->Click += gcnew EventHandler(this, &LoginForm::OnLogin);

        card->Controls->Add(title); card->Controls->Add(lblL); card->Controls->Add(txtLogin); card->Controls->Add(lblP); card->Controls->Add(txtPass); card->Controls->Add(btn);
        this->Controls->Add(card);
    }
    void OnLogin(Object^ sender, EventArgs^ e) {
        if (txtLogin->Text == "admin" && txtPass->Text == "admin") { AdminForm^ f = gcnew AdminForm(); f->Show(); this->Hide(); }
        else if (txtLogin->Text == "student" && txtPass->Text == "student") { StudentForm^ f = gcnew StudentForm(); f->Show(); this->Hide(); }
        else MessageBox::Show(L"Ошибка доступа!");
    }
};

[STAThreadAttribute]
int main(array<String^>^ args) { Application::EnableVisualStyles(); Application::Run(gcnew LoginForm()); return 0; }