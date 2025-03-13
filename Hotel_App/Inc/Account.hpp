/********************************************************************
 * @file    Account.hpp
 * @brief   Quản lý tài khoản của nhân viên và quản lý khách sạn.
 * @details Lớp `Account` cung cấp các phương thức để đăng ký, 
 *          xác thực và quản lý tài khoản người dùng trong hệ thống.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 *******************************************************************/

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include "Std_Types.hpp"
#include <vector>


/**
 * @class Account
 * @brief Lớp đại diện cho tài khoản người dùng.
 */
class Account 
{
    private:
        string username;  /**< Tên tài khoản của người dùng */
        string password;  /**< Mật khẩu */

    public:
        /**
         * @brief Constructor mặc định, tạo tài khoản mặc định cho Manager.
         */
        Account();  

        
        /**
         * @brief Constructor khởi tạo tài khoản với thông tin cụ thể.
         * @param[in] username Tên tài khoản của người dùng.
         * @param[in] password Mật khẩu của tài khoản.
         */
        Account(const string &username, const string &password);


        /**
         * @brief Lấy tên tài khoản.
         * @return std::string - Tên tài khoản.
         */
        string getUsername() const;


        /**
         * @brief Lấy mật khẩu tài khoản.
         * @return std::string - Mật khẩu tài khoản.
         */
        string getPassword() const;


        /**
         * @brief Cập nhật mật khẩu tài khoản.
         * @param[in] password Mật khẩu mới cần đặt.
         */
        void setPassword(const string &password);


        /**
         * @brief Kiểm tra tài khoản đã tồn tại trong danh sách hay chưa.
         * @param[in] accountList Danh sách tài khoản hiện có.
         * @param[in] username Tên tài khoản cần kiểm tra.
         * @return true nếu tài khoản tồn tại, false nếu không.
         */
        static bool accountExists(const vector<Account> &accountList, const string& username);


        /**
         * @brief Đăng ký tài khoản mới.
         * @param[in,out] accountList Danh sách tài khoản cần cập nhật.
         * @param[in] username Tên tài khoản mới.
         * @param[in] password Mật khẩu mới.
         * @return true nếu đăng ký thành công, false nếu thất bại.
         */
        static bool registerAccount(vector<Account> &accountList, const string &username, const string &password);
        

        /**
         * @brief Đăng nhập vào hệ thống.
         * @param[in] accountList Danh sách tài khoản hiện có.
         * @param[in] username Tên tài khoản cần đăng nhập.
         * @param[in] password Mật khẩu cần xác thực.
         * @return true nếu đăng nhập thành công, false nếu thất bại.
         */
        static bool login(const vector<Account> &accountList, const string &username, const string &password);


        /**
         * @brief Xác thực tài khoản của Manager.
         * @param[in] password Mật khẩu cần kiểm tra.
         * @return true nếu đúng mật khẩu của Manager, false nếu không.
         */
        static bool VerifyManagerAccount(const string& password);

        /**
         * @brief Hiển thị danh sách tài khoản có trong hệ thống.
         */
        static void showListAccount();
};

/**< Danh sách chứa tài khoản nhân viên và quản lý. */
extern vector<Account> accountList; 

#endif // ACCOUNT_HPP
