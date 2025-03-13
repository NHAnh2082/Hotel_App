/********************************************************
 * @file    Employee.hpp
 * @brief   Lớp đại diện cho nhân viên trong hệ thống.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include "File_Handling.hpp"
#include "Std_Types.hpp"
#include "Menu.hpp"

class File_Handle;

/**
 * @enum session
 * @brief Định nghĩa các ca làm việc của nhân viên.
 */
typedef enum
{
    none,      /**< Không có ca làm việc */
    morning,   /**< Ca sáng */
    afternoon, /**< Ca chiều */
    evening    /**< Ca tối */
} session;


/**
 * @enum dayinWeek
 * @brief Định nghĩa các ngày trong tuần làm việc.
 */
typedef enum 
{
    Mon,      /**< Thứ 2 */
    Tue,      /**< Thứ 3 */
    Wed,      /**< Thứ 4 */
    Thu,      /**< Thứ 5 */
    Fri,      /**< Thứ 6 */
    totalday  /**< Tổng số ngày làm việc */
} dayinWeek;


/**
 * @typedef Schedule
 * @brief Danh sách ca làm việc của nhân viên.
 */
typedef map<dayinWeek, vector<session>> Schedule;


/**
 * @class Employee
 * @brief Lớp lưu trữ thông tin nhân viên.
 */
class Employee 
{
    private:
        // Thông tin nhân viên
        string id;                  /**< ID tự động */ 
        string name;                /**< Tên nhân viên */
        string phoneNumber;         /**< Số điện thoại */
        string position;            /**< Vị trí công việc */
        string workShift;           /**< Ca làm việc */
        string workingHours;        /**< Giờ làm việc */

        Schedule schedule;          /**< Lịch trình làm việc của nhân viên */


        File_Handle *file_Employee; /**< Con trỏ đến đối tượng xử lý file */
        GuessEmployee guessEmp;     /**< Đối tượng quản lý thông tin khách thuê */
    
        /**
         * @brief Hiển thị ca làm việc của nhân viên.
         * @param[in] user_name Tên người dùng.
         */
        void ReviewWorkshift(const string& user_name);


        /**
         * @brief Chỉnh sửa thông tin nhân viên.
         * @param[in] user_name Tên người dùng.
         */
        void EditInfoEmployee(const string& user_name);


        /**
         * @brief Đặt phòng cho khách hàng.
         */
        void BookRoom();


        /**
         * @brief Hủy đặt phòng của khách hàng.
         */
        void UnbookRoom();


        /**
         * @brief Hiển thị danh sách phòng.
         */
        void ShowRoom();


        /**
         * @brief Lưu thông tin khách thuê.
         */
        void SaveGuessInfo();


        /**
         * @brief Xác định vị trí của nhân viên dựa trên tên tài khoản.
         * @param[in] user_name Tên người dùng.
         * @return std::string - Vị trí của nhân viên.
         */
        string ReturnPosition(const string& user_name);

    public:
        /**
         * @brief Constructor mặc định của Employee dùng để đọc dữ liệu nhân viên từ Database.
         */
        Employee();
        

        /**
         * @brief Constructor khởi tạo thông tin nhân viên.
         * @param[in] _id ID nhân viên.
         * @param[in] _name Tên nhân viên.
         * @param[in] _phoneNumber Số điện thoại nhân viên.
         * @param[in] _position Chức vụ nhân viên.
         */
        Employee(const string &_id, const string &_name, const string &_phoneNumber, const string &_position)
            : id(_id), name(_name), phoneNumber(_phoneNumber), position(_position), workShift("Chưa setup") 
        {
            for (size_t day=Mon; day<totalday; day++)
            {
                schedule[static_cast<dayinWeek>(day)] = {}; // chưa khởi tạo thời gian làm việc
            }
        }


        /**
         * @brief Lấy ID nhân viên.
         * @return std::string - ID của nhân viên.
         */
        string getId() const { return id; }


        /**
         * @brief Lấy tên nhân viên.
         * @return std::string - Tên nhân viên.
         */
        string getName() const { return name; }


        /**
         * @brief Lấy số điện thoại nhân viên.
         * @return std::string - Số điện thoại nhân viên.
         */
        string getPhoneNumber() const { return phoneNumber; }


        /**
         * @brief Lấy vị trí làm việc của nhân viên.
         * @return std::string - Vị trí làm việc.
         */
        string getPosition() const 
        { 
            if (position == "LT") return "Lễ Tân";
            else if (position == "TV") return "Tạp Vụ";
            else if (position == "BV") return "Bảo Vệ";
            else if (position == "DB") return "Đầu Bếp";
            return "";
        }


        /**
         * @brief Lấy ca làm việc của nhân viên.
         * @return std::string - Chuỗi biểu diễn ca làm việc.
         */
        string getWorkShift() const { return workShift; }

        
        /**
         * @brief Lấy số giờ làm việc của nhân viên.
         * @return std::string - Giờ làm việc.
         */
        string getWorkingHours() const { return workingHours; }


        /**
         * @brief Lấy lịch trình làm việc của nhân viên.
         * @return Schedule - Danh sách lịch làm việc.
         */
        Schedule getSchedule() const { return schedule; }


        /**
         * @brief Cập nhật tên nhân viên.
         * @param[in] _name Tên mới của nhân viên.
         */
        void setName(const string &_name) { name = _name; }


        /**
         * @brief Cập nhật vị trí làm việc của nhân viên.
         * @param[in] _position Chức vụ mới.
         */
        void setPosition(const string &_position){ position = _position; }


        /**
         * @brief Cập nhật ca làm việc của nhân viên.
         * @param[in] _workShift Ca làm việc mới.
         */
        void setWorkShift(const string &_workShift){ workShift = _workShift; }


        /**
         * @brief Cập nhật thời gian làm việc của nhân viên.
         * @param[in] _hours Giờ làm việc mới.
         */
        void setWorkingHours(const string &_hours){ workingHours = _hours; }


        /**
         * @brief Cập nhật lịch trình làm việc của nhân viên.
         * @param[in] day Ngày trong tuần.
         * @param[in] sess Ca làm việc.
         */
        void setSchedule(const dayinWeek &day, const session &sess) 
        { 
            schedule[day].push_back(sess); 
        }

        
        /**
         * @brief Hiển thị menu của nhân viên.
         * @param[in] user_name Tên người dùng.
         */
        void ShowEmployeeMenu(const string& user_name);
};

#endif // EMPLOYEE_HPP