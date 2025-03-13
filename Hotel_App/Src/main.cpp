#include "..\\Inc\\Account.hpp"
#include "..\\Inc\\Manager.hpp"
#include "..\\Inc\\Employee_Manager.hpp"
#include "..\\Inc\\File_Handling.hpp"
#include <iostream>
#include <vector>

int main() {

    // EmployeeManager employeeManager;

    // // Thêm nhân viên mới
    // employeeManager.addEmployee(accountList, "Trung", "123456789", "Tạp vụ");
    // employeeManager.addEmployee(accountList, "Thái", "567891237", "Bảo vệ");
    // employeeManager.addEmployee(accountList, "Sơn", "123897519", "Đầu bếp");
    // employeeManager.addEmployee(accountList, "Nam", "987654321", "Lễ Tân");

    // // Hiển thị danh sách nhân viên
    // employeeManager.listEmployees();

    // // Sửa thông tin nhân viên theo tên
    // employeeManager.editEmployeeByName("Trung", "Trung Nguyen", "Quản lý Tạp vụ");

    // // Xóa nhân viên theo ID (số điện thoại)
    // employeeManager.deleteEmployeeById("567891237");

    // // Hiển thị lại danh sách nhân viên
    // employeeManager.listEmployees();


    // Thêm tài khoản mẫu để kiểm tra
    // Account adminAccount("admin", "123456");  // Tài khoản admin
    // Account employeeAccount("user", "123456"); // Tài khoản người dùng
    // accountList.push_back(adminAccount);
    // accountList.push_back(employeeAccount);

    // std::string account, password;

    // std::cout << "\n---- Thông tin đăng nhập ----" << std::endl;
    
    // // Nhập tài khoản (có thể là số điện thoại hoặc account)
    // std::cout << "Nhập tài khoản (account/sđt): ";
    // std::cin >> account;

    // // Nhập mật khẩu
    // std::cout << "Nhập mật khẩu: ";
    // std::cin >> password;

    // // Kiểm tra đăng nhập
    // if (Account::login(accountList, account, password)) {
    //     std::cout << "Đăng nhập thành công!" << std::endl;

    //     // Kiểm tra nếu tài khoản là "admin"
    //     if (account == "admin") {
    //         std::cout << "Xin chào Quản lý!" << std::endl;
    //         Manager manager;
    //         manager.showManagementMenu();  // Hiển thị menu quản lý
    //     } else {
    //         std::cout << "Xin chào người dùng!" << std::endl;
    //         // Gọi menu người dùng (nếu cần thêm chức năng cho người dùng bình thường)
    //     }

    // } else {
    //     std::cout << "Đăng nhập thất bại! Tài khoản hoặc mật khẩu không đúng." << std::endl;
    // }

    Account account;
    Manager manager;
    Employee employee;
    File_Handle file_manager;

    while (1)
    {
        cout << "\n---- Thông tin đăng nhập ----" << endl;
        string account, password;
        cout << "nhập tài khoản (account/sdt): ";
        cin >> account;
        cout << "Nhập mật khẩu: ";
        cin >> password;

        if (Account::login(accountList, account, password)) 
        {
            cout << "Đăng nhập thành công!" << endl;

            // Kiểm tra nếu tài khoản là "admin"
            if (Account::VerifyManagerAccount(password)) 
            {
                cout << "Xin chào Quản lý!" << endl;
                manager.showManagementMenu();  // Hiển thị menu quản lý
            }
            else
            {
                cout << "Xin chào người dùng!" << endl;
                employee.ShowEmployeeMenu(account);
            }
        } 
        else    
            cout << "Đăng nhập thất bại! Tài khoản hoặc mật khẩu không đúng." << endl;
    }

    file_manager.SaveData(EMPLOYEE_CSV_PATH, EMPLOYEE_CSV);
    file_manager.SaveData(ROOM_CSV_PATH, ROOM_CSV);
    file_manager.SaveData(SERVICE_CSV_PATH, SERVICE_CSV);
    file_manager.SaveData(GUESS_CSV_PATH, GUESS_CSV);
    UI::showMessage("Dữ liệu đã được lưu trước khi thoát chương trình.");
    
    return 0;
}
