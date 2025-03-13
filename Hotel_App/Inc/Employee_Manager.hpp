/***********************************************************************
 * @file    Employee_Manager.hpp
 * @brief   Quản lý danh sách nhân viên, bao gồm thêm, sửa, xóa nhân viên.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 **********************************************************************/

#ifndef EMPLOYEE_MANAGER_HPP
#define EMPLOYEE_MANAGER_HPP

#include "Std_Types.hpp"
#include "Employee.hpp"
#include "Account.hpp"
#include <vector>

/**
 * @class EmployeeManager
 * @brief Lớp quản lý nhân viên, thực hiện các thao tác quản lý nhân sự.
 */
class EmployeeManager 
{
    private:
        
        int employeeCounter_ = 0;  /**< Biến đếm số lượng nhân viên để tạo ID tự động */

        /**
         * @brief Tạo ID tự động cho nhân viên mới dựa vào chức vụ.
         * @param[in] position Chức vụ của nhân viên.
         * @return std::string - ID được tạo.
         */
        string generateEmployeeId(const string &position);
        

        /**
         * @brief Tìm nhân viên theo ID.
         * @param[in] id ID của nhân viên cần tìm.
         * @return Con trỏ tới đối tượng `Employee`, hoặc `nullptr` nếu không tìm thấy.
         */
        Employee* findEmployeeById(const string &id);


        /**
         * @brief Cài đặt ca làm việc từ chuỗi nhập từ bàn phím.
         * @param[in,out] employee Đối tượng nhân viên cần cập nhật.
         * @param[in] workshift Chuỗi biểu diễn ca làm việc.
         * @return true nếu cập nhật thành công, false nếu thất bại.
         */
        bool setWorkshiftfromString(Employee &employee, const string &workshift);

    public:
        /**
         * @brief Thêm nhân viên mới với ID tự động.
         * @param[in,out] accountList Danh sách tài khoản.
         * @param[in] name Tên nhân viên.
         * @param[in] phoneNumber Số điện thoại nhân viên.
         * @param[in] position Chức vụ nhân viên.
         */
        void addEmployee(vector<Account> &accountList, const string &name, const string &phoneNumber, const string &position);


        /**
         * @brief Sửa thông tin nhân viên dựa trên ID.
         * @param[in] id ID nhân viên cần sửa.
         * @param[in] newName Tên mới của nhân viên.
         * @param[in] newPosition Chức vụ mới của nhân viên.
         */
        void editEmployeeById(const string &id, const string &newName, string &newPosition);
        

        /**
         * @brief Xóa nhân viên dựa trên ID.
         * @param[in] id ID của nhân viên cần xóa.
         */
        void deleteEmployeeById(const string &id);
        

        /**
         * @brief Set ca làm việc cho nhân viên.
         * @param[in] id ID của nhân viên cần set ca làm.
         * @param[in] shift Chuỗi biểu diễn ca làm việc.
         */
        void setWorkShift(const string &id, const string &shift);
        

        /**
         * @brief Hiển thị danh sách tất cả nhân viên.
         */
        void listEmployees() const;


        /**
         * @brief Hiển thị bảng ca làm việc của tất cả nhân viên.
         */
        void ShowWorkshiftTable(const string &phone = "");


        /**
         * @brief Chỉnh sửa mật khẩu bởi chính nhân viên
         */
        static bool editEmployeePassword(vector<Account> &accountList, const string &user_name, const string &old_pass, const string &new_pass);
};

/**< Danh sách nhân viên */
extern vector<Employee> list_employees;

#endif // EMPLOYEEMANAGER_HPP