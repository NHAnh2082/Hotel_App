/********************************************************
 * @file    File_Handling.hpp
 * @brief   Quản lý việc đọc/ghi dữ liệu từ các file .csv.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef FILE_HANDLING_HPP
#define FILE_HANDLING_HPP

// #include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <future>

#include "Account.hpp"
#include "Guess_Employee.hpp"
#include "Employee_Manager.hpp"
#include "Room_Manager.hpp"
#include "Service_Manager.hpp"

/** @def GUESS_CSV_PATH
 *  @brief Định nghĩa đường dẫn đến file CSV của khách hàng.
 */
#define GUESS_CSV_PATH ".\\database\\guess.csv"


/** @def ROOM_CSV_PATH
 *  @brief Định nghĩa đường dẫn đến file CSV của phòng.
 */
#define ROOM_CSV_PATH ".\\database\\room.csv"


/** @def SERVICE_CSV_PATH
 *  @brief Định nghĩa đường dẫn đến file CSV của dịch vụ.
 */
#define SERVICE_CSV_PATH ".\\database\\service.csv"


/** @def EMPLOYEE_CSV_PATH
 *  @brief Định nghĩa đường dẫn đến file CSV của nhân viên.
 */
#define EMPLOYEE_CSV_PATH ".\\database\\employee.csv"


/** @def FILE_EMPTY
 *  @brief Định nghĩa trạng thái file rỗng.
 */
#define FILE_EMPTY 2


/** @def FILE_NOT_EMPTY
 *  @brief Định nghĩa trạng thái file có dữ liệu.
 */
#define FILE_NOT_EMPTY 3


/**
 * @enum Storage_dtype
 * @brief Xác định loại dữ liệu được lưu trữ trong file CSV.
 */
typedef enum
{
    GUESS_CSV,   /**< Dữ liệu khách thuê */
    ROOM_CSV,    /**< Dữ liệu phòng */
    SERVICE_CSV, /**< Dữ liệu dịch vụ */
    EMPLOYEE_CSV /**< Dữ liệu nhân viên */
} Storage_dtype;


/**
 * @class File_Handle
 * @brief Lớp xử lý thao tác đọc/ghi file CSV.
 */
class File_Handle
{
    public:
        /**
         * @brief Lưu dữ liệu vào file CSV.
         * @param[in] path Đường dẫn đến file CSV.
         * @param[in] type Loại dữ liệu cần lưu.
         * @return true nếu lưu thành công, false nếu thất bại.
         */
        bool SaveData(const string& path, Storage_dtype type);


        /**
         * @brief Đọc dữ liệu từ file CSV.
         * @param[in] path Đường dẫn đến file CSV.
         * @param[in] type Loại dữ liệu cần đọc.
         * @return FILE_NOT_EMPTY nếu file có dữ liệu, FILE_EMPTY nếu file rỗng, false nếu thất bại.
         */
        int LogData(const string& path, Storage_dtype type);

    private:
        /**
         * @brief Lưu dữ liệu khách thuê vào file CSV.
         * @param[in] file Con trỏ file cần ghi.
         */
        void SaveGuessInfo(ofstream &file);


        /**
         * @brief Lưu dữ liệu phòng vào file CSV.
         * @param[in] file Con trỏ file cần ghi.
         */
        void SaveRoomInfo(ofstream &file);


        /**
         * @brief Lưu dữ liệu dịch vụ vào file CSV.
         * @param[in] file Con trỏ file cần ghi.
         */
        void SaveServiceInfo(ofstream &file);


        /**
         * @brief Lưu dữ liệu nhân viên vào file CSV.
         * @param[in] file Con trỏ file cần ghi.
         */
        void SaveEmployeeInfo(ofstream &file);


        /**
         * @brief Đọc dữ liệu khách thuê từ file CSV.
         * @param[in] line Chuỗi chứa dữ liệu đọc từ file.
         */
        void LogGuessInfo(const string& line);


        /**
         * @brief Đọc dữ liệu phòng từ file CSV.
         * @param[in] line Chuỗi chứa dữ liệu đọc từ file.
         */
        void LogRoomInfo(const string& line);


        /**
         * @brief Đọc dữ liệu dịch vụ từ file CSV.
         * @param[in] line Chuỗi chứa dữ liệu đọc từ file.
         */
        void LogServiceInfo(const string& line);


        /**
         * @brief Đọc dữ liệu nhân viên từ file CSV.
         * @param[in] line Chuỗi chứa dữ liệu đọc từ file.
         */
        void LogEmployeeInfo(const string& line);
};

#endif // FILE_HANDLING_HPP 