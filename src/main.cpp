#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

// --- 1. Форма Администратора ---
public ref class AdminForm : public Form {
private:
    DataGridView^ gridUsers;
    TextBox^ txtFio;
    ComboBox^ cbRole;
    Button^ btnAdd;
    int nextId = 3; // Простой счетчик ID

public:
    AdminForm() {
        this->Text = L"Панель Администратора - EduSystem";
        this->Size = System::Drawing::Size(750, 450);
        this->StartPosition = FormStartPosition::CenterScreen;

        Label^ lblTitle = gcnew Label();
        lblTitle->Text = L"Управление базой данных пользователей";
        lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
        lblTitle->AutoSize = true;
        lblTitle->Location = Point(20, 20);

        // Поля для добавления пользователя
        Label^ lblFio = gcnew Label();
        lblFio->Text = L"ФИО:";
        lblFio->Location = Point(20, 70);
        lblFio->AutoSize = true;

        txtFio = gcnew TextBox();
        txtFio->Location = Point(60, 67);
        txtFio->Width = 200;

        Label^ lblRole = gcnew Label();
        lblRole->Text = L"Роль:";
        lblRole->Location = Point(280, 70);
        lblRole->AutoSize = true;

        cbRole = gcnew ComboBox();
        cbRole->Items->Add(L"Студент");
        cbRole->Items->Add(L"Преподаватель");
        cbRole->SelectedIndex = 0;
        cbRole->Location = Point(320, 67);
        cbRole->Width = 150;
        cbRole->DropDownStyle = ComboBoxStyle::DropDownList;

        btnAdd = gcnew Button();
        btnAdd->Text = L"+ Добавить";
        btnAdd->Location = Point(490, 65);
        btnAdd->Width = 120;
        btnAdd->BackColor = Color::LightGreen;
        btnAdd->Click += gcnew EventHandler(this, &AdminForm::OnAddClick);

        // Таблица пользователей
        gridUsers = gcnew DataGridView();
        gridUsers->Location = Point(20, 110);
        gridUsers->Size = System::Drawing::Size(690, 280);
        gridUsers->ColumnCount = 3;
        gridUsers->Columns[0]->Name = L"ID";
        gridUsers->Columns[1]->Name = L"ФИО пользователя";
        gridUsers->Columns[2]->Name = L"Назначенная Роль";
        gridUsers->Columns[1]->Width = 250;
        gridUsers->Columns[2]->Width = 150;
        gridUsers->AllowUserToAddRows = false; // Отключаем пустую строку снизу
        gridUsers->ReadOnly = true;

        // Добавляем стартовые данные
        gridUsers->Rows->Add(L"#001", L"Вяльцев М.А.", L"Студент");
        gridUsers->Rows->Add(L"#002", L"Смирнов А.П.", L"Преподаватель");

        this->Controls->Add(lblTitle);
        this->Controls->Add(lblFio);
        this->Controls->Add(txtFio);
        this->Controls->Add(lblRole);
        this->Controls->Add(cbRole);
        this->Controls->Add(btnAdd);
        this->Controls->Add(gridUsers);
    }

    void OnAddClick(Object^ sender, EventArgs^ e) {
        if (String::IsNullOrWhiteSpace(txtFio->Text)) {
            MessageBox::Show(L"Введите ФИО пользователя!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        String^ newId = L"#00" + nextId.ToString();
        gridUsers->Rows->Add(newId, txtFio->Text, cbRole->Text);
        nextId++;
        txtFio->Clear(); // Очищаем поле после добавления
    }
};

// --- 2. Форма Студента ---
public ref class StudentForm : public Form {
private:
    ComboBox^ cbDocType;
    Button^ btnOrder;

public:
    StudentForm() {
        this->Text = L"Личный кабинет Студента";
        this->Size = System::Drawing::Size(650, 450);
        this->StartPosition = FormStartPosition::CenterScreen;

        Label^ lblTitle1 = gcnew Label();
        lblTitle1->Text = L"Электронная зачетка";
        lblTitle1->Font = gcnew System::Drawing::Font(L"Segoe UI", 12, FontStyle::Bold);
        lblTitle1->AutoSize = true;
        lblTitle1->Location = Point(20, 20);

        // Таблица успеваемости
        DataGridView^ gridGrades = gcnew DataGridView();
        gridGrades->Location = Point(20, 50);
        gridGrades->Size = System::Drawing::Size(590, 150);
        gridGrades->ColumnCount = 3;
        gridGrades->Columns[0]->Name = L"Дисциплина";
        gridGrades->Columns[1]->Name = L"Тип контроля";
        gridGrades->Columns[2]->Name = L"Оценка";
        gridGrades->Columns[0]->Width = 250;
        gridGrades->AllowUserToAddRows = false;
        gridGrades->ReadOnly = true;

        gridGrades->Rows->Add(L"Базы данных", L"Экзамен", L"Отлично (5)");
        gridGrades->Rows->Add(L"Разработка мобильных приложений", L"Диф. зачет", L"Отлично (5)");
        gridGrades->Rows->Add(L"Иностранный язык", L"Зачет", L"Зачтено");

        Label^ lblTitle2 = gcnew Label();
        lblTitle2->Text = L"Заказ справок";
        lblTitle2->Font = gcnew System::Drawing::Font(L"Segoe UI", 12, FontStyle::Bold);
        lblTitle2->AutoSize = true;
        lblTitle2->Location = Point(20, 230);

        Label^ lblDoc = gcnew Label();
        lblDoc->Text = L"Тип документа:";
        lblDoc->Location = Point(20, 270);
        lblDoc->AutoSize = true;

        cbDocType = gcnew ComboBox();
        cbDocType->Items->Add(L"Справка об обучении (в военкомат)");
        cbDocType->Items->Add(L"Справка-вызов на сессию");
        cbDocType->Items->Add(L"Академическая справка");
        cbDocType->SelectedIndex = 0;
        cbDocType->Location = Point(120, 267);
        cbDocType->Width = 300;
        cbDocType->DropDownStyle = ComboBoxStyle::DropDownList;

        btnOrder = gcnew Button();
        btnOrder->Text = L"Отправить запрос в деканат";
        btnOrder->Location = Point(120, 310);
        btnOrder->Size = System::Drawing::Size(300, 35);
        btnOrder->BackColor = Color::LightSteelBlue;
        btnOrder->Click += gcnew EventHandler(this, &StudentForm::OnOrderClick);

        this->Controls->Add(lblTitle1);
        this->Controls->Add(gridGrades);
        this->Controls->Add(lblTitle2);
        this->Controls->Add(lblDoc);
        this->Controls->Add(cbDocType);
        this->Controls->Add(btnOrder);
    }

    void OnOrderClick(Object^ sender, EventArgs^ e) {
        String^ msg = L"Заявка на документ:\n\"" + cbDocType->Text + L"\"\nуспешно отправлена в деканат!";
        MessageBox::Show(msg, L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
};

// --- 3. Форма Авторизации (Главная) ---
public ref class LoginForm : public Form {
private:
    TextBox^ txtLogin;
    TextBox^ txtPassword;
    Button^ btnLogin;

public:
    LoginForm() {
        this->Text = L"Авторизация EduSystem";
        this->Size = System::Drawing::Size(350, 300);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;

        Label^ lblMain = gcnew Label();
        lblMain->Text = L"Вход в систему";
        lblMain->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
        lblMain->AutoSize = true;
        lblMain->Location = Point(85, 20);

        Label^ lblHint = gcnew Label();
        lblHint->Text = L"(admin/admin или student/student)";
        lblHint->ForeColor = Color::Gray;
        lblHint->AutoSize = true;
        lblHint->Location = Point(75, 55);

        Label^ lblLogin = gcnew Label();
        lblLogin->Text = L"Логин:";
        lblLogin->Location = Point(75, 90);
        lblLogin->AutoSize = true;

        txtLogin = gcnew TextBox();
        txtLogin->Location = Point(75, 110);
        txtLogin->Width = 180;

        Label^ lblPass = gcnew Label();
        lblPass->Text = L"Пароль:";
        lblPass->Location = Point(75, 150);
        lblPass->AutoSize = true;

        txtPassword = gcnew TextBox();
        txtPassword->Location = Point(75, 170);
        txtPassword->Width = 180;
        txtPassword->PasswordChar = '*';

        btnLogin = gcnew Button();
        btnLogin->Text = L"Войти";
        btnLogin->Location = Point(75, 210);
        btnLogin->Width = 180;
        btnLogin->Height = 35;
        btnLogin->BackColor = Color::CornflowerBlue;
        btnLogin->ForeColor = Color::White;
        btnLogin->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
        btnLogin->Click += gcnew EventHandler(this, &LoginForm::OnLoginClick);

        this->Controls->Add(lblMain);
        this->Controls->Add(lblHint);
        this->Controls->Add(lblLogin);
        this->Controls->Add(txtLogin);
        this->Controls->Add(lblPass);
        this->Controls->Add(txtPassword);
        this->Controls->Add(btnLogin);
    }

    void OnLoginClick(Object^ sender, EventArgs^ e) {
        if (txtLogin->Text == "admin" && txtPassword->Text == "admin") {
            AdminForm^ adminForm = gcnew AdminForm();
            adminForm->Show();
            this->Hide();
        }
        else if (txtLogin->Text == "student" && txtPassword->Text == "student") {
            StudentForm^ studentForm = gcnew StudentForm();
            studentForm->Show();
            this->Hide();
        }
        else {
            MessageBox::Show(L"Ошибка: Неверный логин или пароль!", L"Вход заблокирован", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
};

// --- Точка входа в программу ---
[STAThreadAttribute]
int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew LoginForm());
    return 0;
}