/***********************************************************************
 * @file    Employee_Manager.cpp
 * @brief   Định nghĩa các phương thức của lớp `EmployeeManager`.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 **********************************************************************/
#include "..\\Inc\\Employee_Manager.hpp"
#include "..\\Inc\\UI.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>

/**< Danh sách nhân viên */
vector<Employee> list_employees;


void printSchedule(const Employee& employee)
{
    vector<string> list_session = {"X", "Sáng", "Chiều", "Tối"};

    // In dữ liệu của từng nhân viên
    cout << setw(17) << left << employee.getName();
    cout << " | ";

    // in ra lần lượt các ca làm giống nhau của các ngày trong tuần trên cùng 1 hàng
    bool new_line = false;
    for (int shift = morning; shift <= evening; ++shift)
    {
        if (new_line)
        {
            cout << setw(17) << left << " ";
            cout << " | ";
            new_line = false;
        }

        // Lặp qua từng ngày để in ra tất cả ca làm giống nhau
        for (int day = Mon; day < totalday; ++day)
        {
            // Tìm kiếm ngày trong ca làm của nhân viên 
            auto it = employee.getSchedule().find(static_cast<dayinWeek>(day));

            // Lặp qua từng
            if (it != employee.getSchedule().end() && find(it->second.begin(), it->second.end(), static_cast<session>(shift)) != it->second.end())
            {
                cout << list_session[shift] << "      | ";
            }
            else
            {
                cout << "X         | ";
            }
        }
        new_line = true;
        cout << endl;
    }
   UI::showMessage("---------------------------------------------------------------------------");
}


/**
 * @brief Cài đặt ca làm việc từ chuỗi nhập từ bàn phím.
 * @param[in,out] employee Đối tượng nhân viên cần cập nhật.
 * @param[in] workshift Chuỗi biểu diễn ca làm việc.
 * @return true nếu cập nhật thành công, false nếu thất bại.
 */
bool EmployeeManager::setWorkshiftfromString(Employee &employee, const string &workshift)
{
    employee.setWorkShift(workshift);

    auto parseSession = [](char session)
    {
        switch (toupper(session))
        {
            case 'S': return morning;     // Sáng
            case 'C': return afternoon;   // Chiều
            case 'T': return evening;     // Tối
            default:  return none;        // Không hợp lệ
        }
    };

    auto parseDay = [](char day)
    {
        switch (day)
        {
            case '2': return Mon;      // Thứ 2
            case '3': return Tue;      // Thứ 3
            case '4': return Wed;      // Thứ 4
            case '5': return Thu;      // Thứ 5
            case '6': return Fri;      // Thứ 6
            default:  return totalday; // Không hợp lệ
        };
    };
    
    // Kiểm tra định dạng có hợp lệ
    if (workshift.size() != 3 || workshift[1] != '-') // Định dạng phải là "2-C"
    {
        return FAIL;
    }

    // Parse ngày và ca làm từ chuỗi
    dayinWeek day = parseDay(workshift[0]);
    session sess = parseSession(workshift[2]);

    // Kiểm tra giá trị hợp lệ
    if (day == totalday || sess == none)
    {
        return FAIL;
    }

    // Thêm ca làm vào lịch trình
    employee.setSchedule(day, sess);
    return SUCCESS;
}


/**
 * @brief Tạo ID tự động cho nhân viên mới dựa trên chức vụ.
 * @param[in] position Chức vụ của nhân viên.
 * @return std::string - ID nhân viên.
 */
string EmployeeManager::generateEmployeeId(const string &position) 
{
    employeeCounter_++;
    stringstream ss; // được sử dụng để xây dựng mã với nhiều thành phần (text, số, định dạng)

    // Tạo tiền tố ID theo chức vụ
    if (position == "TV")       ss << "TV";
    else if (position == "BV")  ss << "BV";
    else if (position == "DB")  ss << "DV";
    else if (position == "LT")  ss << "LT"; 
    else ss << "NV";  // Mặc định nếu không có chức vụ đặc biệt

    // Tạo số thứ tự cho ID và đảm bảo có 3 chữ số
    ss << setw(3) << setfill('0') << employeeCounter_;

    return ss.str();
}


/**
 * @brief Thêm nhân viên mới với ID tự động.
 * @param[in,out] accountList Danh sách tài khoản.
 * @param[in] name Tên nhân viên.
 * @param[in] phoneNumber Số điện thoại nhân viên.
 * @param[in] position Chức vụ nhân viên.
 */
void EmployeeManager::addEmployee(vector<Account> &accountList, const string &name, const string &phoneNumber, const string &position) 
{
    // Kiểm tra nếu số điện thoại đã tồn tại trong hệ thống tài khoản
    if (Account::accountExists(accountList, phoneNumber)) 
    {
        UI::showMessage("Số điện thoại này đã được đăng ký.");
        return;
    }

    // Tạo ID tự động cho nhân viên mới
    string id = generateEmployeeId(position);

    // Thêm nhân viên mới vào danh sách
    list_employees.emplace_back(id, name, phoneNumber, position);
    UI::showMessage("Nhân viên " + name + " với ID " + id + " đã được thêm thành công.");

    // lambda tạo mật khẫu ngẫu nhiên với 6 chữ số
    auto generateRandompassword = [=]()
    {
        string pass = "";
        for (int i = 0; i < 6; i++)
        {
            int index = rand() % 10;
            pass += to_string(index);
        }
        return pass;
    };

    // Tự động đăng ký tài khoản cho nhân viên với mật khẩu mặc định
    Account::registerAccount(accountList, phoneNumber, "123456");
    UI::showMessage("Tài khoản cho nhân viên đã được đăng ký với mật khẩu mặc định '123456'.");
}


/**
 * @brief Sửa thông tin nhân viên dựa trên ID.
 * @param[in] id ID nhân viên cần sửa.
 * @param[in] newName Tên mới của nhân viên.
 * @param[in] newPosition Chức vụ mới của nhân viên.
 */
void EmployeeManager::editEmployeeById(const string& id, const string& newName, string& newPosition) 
{
    Employee* employee = findEmployeeById(id);
    
    if (employee) 
    {
        if (newPosition == "TV")        newPosition = "Tạp Vụ";
        else if (newPosition == "BV")   newPosition = "Bảo Vệ";
        else if (newPosition == "LT")   newPosition = "Lễ Tân";
        else if (newPosition == "DB")   newPosition = "Đầu Bếp";
        else newPosition = "Nhân Viên";

        employee->setName(newName);
        employee->setPosition(newPosition);
        UI::showMessage("Thông tin nhân viên đã được cập nhật.");
    } 
    else 
    {
        UI::showMessage("Không tìm thấy nhân viên với tên này.");
    }
}


/**
 * @brief Xóa nhân viên dựa trên ID.
 * @param[in] id ID của nhân viên cần xóa.
 */
void EmployeeManager::deleteEmployeeById(const string &id) 
{
    auto it = remove_if(list_employees.begin(), list_employees.end(), [id](const Employee &emp)
    {
        return emp.getId() == id;
    });

    if (it != list_employees.end()) 
    {
        list_employees.erase(it, list_employees.end());
        UI::showMessage("Nhân viên với ID " + id + " đã được xóa.");
    } 
    else 
    {
        UI::showMessage("Không tìm thấy nhân viên với ID này.");
    }
}


/**
 * @brief Set ca làm việc cho nhân viên.
 * @param[in] id ID của nhân viên cần set ca làm.
 * @param[in] shift Chuỗi biểu diễn ca làm việc.
 */
void EmployeeManager::setWorkShift(const string &id, const string &shift) 
{
    Employee *employee = findEmployeeById(id);

    if (employee == nullptr) 
    {
        UI::showMessage("Không tìm thấy nhân viên với ID: " + id);
        return;
    }

    employee->setWorkShift(shift);

    UI::showMessage("Ca làm việc của nhân viên " + employee->getName() + " đã được cập nhật thành công thành: " + shift);

    if (setWorkshiftfromString(*employee, shift))
    {
        UI::showMessage("Ca làm việc của nhân viên " + employee->getName() + " đã được cập nhật thành công thành: " + shift);
    }
    else
    {
        cout << "chuỗi sai định dạng hoặc không hợp lệ" << endl;
    }
}


/**
 * @brief Hiển thị danh sách tất cả nhân viên.
 */
void EmployeeManager::listEmployees() const 
{
    if (list_employees.empty())
    {
        UI::showMessage("Không có nhân viên nào.");
        return;
    } 
    
    for (const auto &employee : list_employees) 
    {
        UI::showMessage("ID: " + employee.getId() + 
                        ", Tên: " + employee.getName() + 
                        ", Số điện thoại: " + employee.getPhoneNumber() + 
                        ", Chức vụ: " + employee.getPosition() +
                        ", Ca làm: " + employee.getWorkShift());
    }

    // cout << left << setw(10) <<  "ID" << setw(15) << "Tên" << setw(25) << "Số điện thoại" << setw(15) << "Chức vụ" <<  setw(15) << "Ca làm" << endl;
    // cout << setfill('-') << setw(70) << "-" << endl;
    // // Reset fill về mặc định (space)
    // cout << setfill(' ');

    // for (const auto &employee : list_employee)
    // {
    //      cout << left << setw(10) <<  employee.getId() 
    //                   << setw(15) << employee.getName()  
    //                   << setw(17) << employee.getPhoneNumber() 
    //                   << setw(12) <<  employee.getPosition()
    //                   << setw(10) << employee.getWorkshift()  
    //                   << endl;
    // }
}


/**
 * @brief Tìm nhân viên theo ID.
 * @param[in] id ID nhân viên cần tìm.
 * @return Con trỏ tới đối tượng Employee hoặc nullptr nếu không tìm thấy.
 */
Employee* EmployeeManager::findEmployeeById(const string& id) 
{
    for (auto &employee : list_employees) 
    {
        if (employee.getId() == id) return &employee;
    }
    return nullptr;
}


/**
 * @brief Chỉnh sửa mật khẩu bởi chính nhân viên
 */
bool EmployeeManager::editEmployeePassword(vector<Account> &accountList, const string &user_name, const string &old_pass, const string &new_pass)
{
    // đảm bảo mật khẩu mới hợp lệ
    if (new_pass.length() != 6) return FAIL;

    for (auto &account : accountList)
    {
        if (account.getPassword() == old_pass && account.getUsername() == user_name)
        {
            account.setPassword(new_pass);
            return SUCCESS;
        }
    }
    return FAIL;
}


/**
 * @brief Hiển thị bảng ca làm việc của tất cả nhân viên.
 */
void EmployeeManager::ShowWorkshiftTable(const string &phone)
{
    if (list_employees.empty()) 
    {
        UI::showMessage("Chưa có nhân viên");
        return;
    }

    std::vector<std::string> list_day = {"T2", "T3", "T4", "T5", "T6"};
    std::cout << "Tên nhân viên     | ";

    for (const auto &day : list_day) 
    {
        std::cout << day << "         | ";
    }
    std::cout << std::endl;

    // Nếu `phone` không rỗng, chỉ hiển thị nhân viên có số điện thoại này
    for (const auto &employee : list_employees) 
    {
        if (phone.empty() || employee.getPhoneNumber() == phone) 
        {
            printSchedule(employee);
        }
    }

    UI::showMessage("----------------------------------------------------------");
}


/**
 * @brief Constructor mặc định của Employee dùng để đọc dữ liệu nhân viên từ Database.
 */
Employee::Employee()
{
        int read_result = file_Employee->LogData(GUESS_CSV_PATH,GUESS_CSV);

        if (read_result == FILE_EMPTY)
        {
            UI::showMessage("Chưa có thông tin khách đặt phòng");
        }
        else if (read_result== FAIL)
        {
            UI::showMessage("Tải thông tin khách thất bại");
        }
        else
        {
            UI::showMessage("Tải thông tin khách thành công");
        }
}


/**
 * @brief Hiển thị menu của nhân viên.
 * @param[in] user_name Tên người dùng.
 */
void Employee::ShowEmployeeMenu(const string& user_name)
{
    if (ReturnPosition(user_name) == "LỄ TÂN")
    {
        Menu menu{"------" + ReturnPosition(user_name) + "------", 
        {
            {1, "Xem ca làm việc"    , [this, user_name](){ ReviewWorkshift(user_name) ;}},
            {2, "Sửa thông tin"      , [this, user_name](){ EditInfoEmployee(user_name);}},
            {3, "Đặt phòng cho khách", [this](){ BookRoom()      ;}},
            {4, "Trả phòng cho khách", [this](){ UnbookRoom()    ;}},
            {5, "Danh sách phòng"    , [this](){ ShowRoom()      ;}},
            {6, "Lữu trữ thông tin"  , [this](){ SaveGuessInfo() ;}},
            {0, "Quay lại"           , [](){ UI::showMessage("Vui lòng chọn tính năng");}}
        }};
        menu.showMenu();
    }
    else
    {
        Menu menu{"------" + ReturnPosition(user_name) + "------", 
        {
            {1, "Xem ca làm việc", [this,user_name](){ ReviewWorkshift(user_name)  ;}},
            {2, "Sửa thông tin"  , [this,user_name](){ EditInfoEmployee(user_name) ;}},
            {0, "Quay lại"       , [](){ UI::showMessage("Vui lòng chọn tính năng");}}
        }};
        menu.showMenu();
    }
}


/**
 * @brief Hiển thị ca làm việc của nhân viên.
 * @param[in] user_name Tên người dùng.
 */
void Employee::ReviewWorkshift(const string& user_name)
{       
    UI::showMessage("-------- CA LÀM VIỆC --------");

    EmployeeManager employeeManager; // Tạo đối tượng EmployeeManager
    
    while(1)
    {
        employeeManager.ShowWorkshiftTable(user_name);

        inputvalidchoice:
            int choice = UI::getUserChoice("Nhập 0 để quay lại: ");

            if(choice == 0)
            {
                system("cls");
                break;
            }
            else
            {
                UI::showMessage("Lựa chọn không hợp lệ");
                goto inputvalidchoice;
            }
    }
}


/**
 * @brief Chỉnh sửa thông tin nhân viên.
 * @param[in] user_name Tên người dùng.
 */
void Employee::EditInfoEmployee(const string& user_name)
{
    UI::showMessage("--------SỬA THÔNG TIN--------");
    
    while (1)
    {
        UI::showMessage("Vui lòng nhập mật khẩu có 6 chữ số");
        UI::showMessage("----------------------------------");

        string old_password = UI::getInputString("Vui lòng nhập mật khẩu cũ:  ");
        string new_password = UI::getInputString("Vui lòng nhập mật khẩu mới: ");

        // kiểm tra mật khẩu mới có hợp không và mật khẩu cũ có khớp với sdt của nhân viên hiện tại không
        if (EmployeeManager::editEmployeePassword(accountList,user_name,old_password,new_password) == FAIL)
        {
            UI::showMessage("Mật khẩu không đúng hoặc không hợp lệ");
        }

        UI::showMessage("\nThay đổi mật khẩu thành cồng");
        UI::showMessage("------------------------------");

    Inputvalidchoice:
        UI::showMessage("1.Tiếp tục sửa thông tin");
        UI::showMessage("0.Quay lại");

        int choice = UI::getUserChoice("Vui lòng nhập lựa chọn: ");
        if (choice == 0) 
        {
            system("cls");
            break;
        }
        else
        {
            if(choice != 1)
            {
                UI::showMessage("Lựa chọn không hợp lệ! Vui lòng chọn lại\n");
                goto Inputvalidchoice;
            }
        }
    }
}


/**
 * @brief Đặt phòng cho khách hàng.
 */
void Employee::BookRoom()
{
    UI::showMessage("--------ĐẶT PHÒNG CHO KHÁCH--------");
    
    while (1)
    {
        if (guessEmp.ShowListRoomAvailable() == FAIL)
        {
            UI::showMessage("Chua co phong nao duoc them");
        }

        UI::showMessage("X.Đang Sử Dụng");
        UI::showMessage("O.Đang Trống");

        InputValidRoom:
            int room = UI::getUserChoice("Vui lòng chọn phòng:");

            if (RoomManager::IsRoomAvailableExist(room) == NOT_EXIST)
            {
                UI::showMessage("Phòng không có sẵn! Vui lòng chọn lại");
                goto InputValidRoom;
            }

            string name    = UI::getInputString("Vui lòng nhập tên khách hàng: ");
            string phone   = UI::getInputString("Vui lòng nhập SDT khách hàng: ");
            string checkin = UI::getInputString("Vui lòng nhập ngày checkin:   ");

            if (guessEmp.BookRoom(room, name, phone, checkin) == SUCCESS)
            {
                UI::showMessage("Đặt phòng thành công");
            }
            else
            {
                UI::showMessage("Phòng đã được đặt");
                goto InputValidRoom;
            }

            UI::showMessage("1.Tiếp tục đặt phòng");
            UI::showMessage("0.Quay lại");

        Inputvalidchoice:
            int choice = UI::getUserChoice("Vui long nhap lua chon:");

            // UI::showMessage("--------------------------------");
            if (choice == 0) 
            {
                system("cls");
                break;
            }
            else
            {
                if(choice != 1)
                {
                    UI::showMessage("Lựa chọn không hợp lệ! Vui lòng chọn lại\n");
                    goto Inputvalidchoice;
                }
            }
    }
}


/**
 * @brief Hủy đặt phòng của khách hàng.
 */
void Employee::UnbookRoom()
{
    UI::showMessage("--------TRẢ PHÒNG CHO KHÁCH--------");

    while (1)
    {
        if(guessEmp.ShowListGuess() == FAIL)
        {
            UI::showMessage("Chưa có khách đặt phòng");
            return;
        }

    InputValidPhone:
        string phone = UI::getInputString("Vui lòng nhập SDT:");
        Guess *guess = guessEmp.GuessInfo(phone);

        if (guess == NULL)
        {
            UI::showMessage("Không tìm thấy khách hàng với SDT " + phone);
            goto InputValidPhone;
        }
        else
        {
            string checkout = UI::getInputString("Vui lòng nhập ngày checkout:");
            guessEmp.UnbookRoom(*guess,checkout);
            guessEmp.ServiceFeedbackInfo(*guess);

            UI::showMessage("Trả phòng cho khách thành công");
            UI::showMessage("------------------------------------");
            UI::showMessage("1.Tiếp tục trả phòng");
            UI::showMessage("0.Quay lai");
            UI::showMessage("--------------------------------");
            
        Inputvalidchoice:
            int choice = UI::getUserChoice("Vui lòng nhập lựa chọn:");

            if (choice == 0) 
            {
                system("cls");
                break;
            }
            else
            {
                if(choice != 1)
                {
                    UI::showMessage("Lựa chọn không hợp lệ! Vui lòng chọn lại\n");
                    goto Inputvalidchoice;
                }
            }
        }
    }
}


/**
 * @brief Hiển thị danh sách phòng.
 */
void Employee::ShowRoom()
{
    UI::showMessage("--------DANH SÁCH PHÒNG--------");

    while (1)
    {
        if (guessEmp.ShowListRoomAvailable() == FAIL)
        {
            UI::showMessage("Chưa có phòng nào được thêm");
        }

        UI::showMessage("X.Đang Sử Dụng");
        UI::showMessage("O.Đang Trống");
        UI::showMessage("-----------------------------");
        UI::showMessage("0.Quay lai");
    Inputvalidchoice:
        int choice = UI::getUserChoice("Vui long nhap lua chon:");

        if (choice == 0) 
        {
            system("cls");
            break;
        }
        else
        {
            if(choice != 1)
            {
                UI::showMessage("Lựa chọn không hợp lệ! Vui lòng chọn lại\n");
                goto Inputvalidchoice;
            }
        }
    }
}


/**
 * @brief Lưu thông tin khách thuê.
 */
void Employee::SaveGuessInfo()
{
    UI::showMessage("---------LƯU THÔNG TIN----------");
    while(1){
        
    Inputvalidchoice:
        UI::showMessage("1.Lưu Danh Sách Khách Đặt Phòng");
        UI::showMessage("0.Quay Lại");

        int choice = UI::getUserChoice("Vui long nhap lua chon:");
        
        if(choice == 1) 
        {
            bool save_result = file_Employee->SaveData(GUESS_CSV_PATH,GUESS_CSV);

            if(save_result == SUCCESS)
            {
                {UI::showMessage("luu tru thanh cong");}
            }
            else
            {
                {UI::showMessage("khong co thong tin");}
            }
            break;
        }
        else if (choice == 0)
        {
            system("cls");
            break;
        }
        else
        {
            if (choice != 1)
            {
                UI::showMessage("Lua chon khong hop le, vui long nhap lai");
                goto Inputvalidchoice;
            }
        }
    }
}


/**
 * @brief Xác định vị trí của nhân viên dựa trên tên tài khoản.
 * @param[in] user_name Tên người dùng.
 * @return std::string - Vị trí của nhân viên.
 */
string Employee::ReturnPosition(const string &user_name)
{
    // duyệt qua danh sách nhân viên
    for(const auto& employee : list_employees)
    {
        // so sánh account và sdt của nhân viên hiện tại
        if(employee.getPhoneNumber() == user_name)
        {
            string position = employee.getPosition();
            if (position == "BV")
            {
                position ="BẢO VỆ";
            }
            else if (position == "LT") 
            {
                position = "LỄ TÂN";
            }
            else if (position == "DB") 
            {
                position = "ĐẦU BẾP";
            }
            else if (position == "TV") 
            {
                position = "TẠP VỤ";
            }
            else
            {
                position = "NHÂN VIÊN";
            }

            return position;
        }
    }

    return string("không hợp lệ");
}