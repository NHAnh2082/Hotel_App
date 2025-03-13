/**************************************************************
 * @file    Manager.hpp
 * @brief   Quản lý hệ thống: nhân viên, phòng, và các dịch vụ.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 *************************************************************/

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "File_Handling.hpp"
#include "Menu.hpp"
#include "UI.hpp"
#include "Employee_Manager.hpp"


/**
 * @class Manager
 * @brief Lớp quản lý hệ thống, bao gồm quản lý nhân viên, phòng, và dịch vụ.
 */
class Manager 
{
    public:
        /**
         * @brief Constructor khởi tạo đối tượng `Manager`.
         */
        Manager();

        /**
         * @brief Hiển thị menu quản lý chính.
         */
        void showManagementMenu();

    private:
        EmployeeManager employeeManager; /**< Quản lý nhân viên */
        RoomManager roomManage;          /**< Quản lý phòng */
        ServiceManager serviceManage;    /**< Quản lý dịch vụ */
        File_Handle file_manager;        /**< Quản lý thao tác với file */

        /**
         * @brief Quản lý nhân viên.
         */
        void manageEmployees();

        /**
         * @brief Quản lý phòng.
         */
        void manageRooms();

        /**
         * @brief Quản lý dịch vụ.
         */
        void manageServices();

        /**
         * @brief Thêm nhân viên mới.
         */
        void addEmployee();

        /**
         * @brief Sửa thông tin nhân viên.
         */
        void editEmployee();

        /**
         * @brief Xóa nhân viên khỏi hệ thống.
         */
        void deleteEmployee();

        /**
         * @brief Hiển thị danh sách nhân viên.
         */
        void listEmployees();

        /**
         * @brief Đặt ca làm việc cho nhân viên.
         */
        void setWorkShift();

        /**
         * @brief Hiển thị bảng thời gian làm việc của nhân viên.
         */
        void TableSchedule();

        /**
         * @brief Thêm phòng mới vào hệ thống.
         */
        void addRoom();

        /**
         * @brief Sửa thông tin phòng.
         */
        void editRoom();

        /**
         * @brief Xóa phòng khỏi hệ thống.
         */
        void deleteRoom();

        /**
         * @brief Hiển thị danh sách phòng trong hệ thống.
         */
        void listRooms();

        /**
         * @brief Thêm dịch vụ mới vào hệ thống.
         */
        void addService();

        /**
         * @brief Sửa thông tin dịch vụ.
         */
        void editService();

        /**
         * @brief Xóa dịch vụ khỏi hệ thống.
         */
        void deleteService();

        /**
         * @brief Hiển thị danh sách dịch vụ hiện có.
         */
        void listServices();

        /**
         * @brief Lưu dữ liệu nhân viên, phòng, và dịch vụ vào file CSV.
         */
        void SaveDataCSV();
};

#endif // MANAGER_HPP
