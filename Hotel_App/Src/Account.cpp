/********************************************************
 * @file    Account.cpp
 * @brief   Định nghĩa các phương thức của lớp `Account`.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#include "..\\Inc\\Account.hpp"

/**< Danh sách tài khoản nhân viên */
vector<Account> accountList; 


/**
 * @brief Constructor mặc định, tạo tài khoản mặc định cho Manager.
 *        Username: AnhNguyen
 *        Password: 20082002
 */
Account::Account()
{
    accountList.emplace_back("AnhNguyen", "20082002");
}


/**
 * @brief Constructor khởi tạo tài khoản với thông tin cụ thể.
 * @param[in] username Tên tài khoản của người dùng.
 * @param[in] password Mật khẩu của tài khoản.
 */
Account::Account(const string& username, const string& password): username(username), password(password){}


/**
 * @brief Lấy tên tài khoản.
 * @return std::string - Tên tài khoản.
 */
string Account::getUsername() const 
{
    return this->username;
}


/**
 * @brief Lấy mật khẩu tài khoản.
 * @return std::string - Mật khẩu tài khoản.
 */
string Account::getPassword() const 
{
    return this->password;
}


/**
 * @brief Cập nhật mật khẩu tài khoản.
 * @param[in] password Mật khẩu mới cần đặt.
 */
void Account::setPassword(const string& password) 
{
    this->password = password;
}


/**
 * @brief Kiểm tra tài khoản đã tồn tại trong danh sách hay chưa.
 * @param[in] accountList Danh sách tài khoản hiện có.
 * @param[in] username Tên tài khoản cần kiểm tra.
 * @return true nếu tài khoản tồn tại, false nếu không.
 */
bool Account::accountExists(const vector<Account>& accountList, const string& username) 
{
    for (const auto &account : accountList) 
    {
        if (account.getUsername() == username) return true;
    }
    return false;
}


/**
 * @brief Đăng ký tài khoản mới.
 * @param[in,out] accountList Danh sách tài khoản cần cập nhật.
 * @param[in] username Tên tài khoản mới.
 * @param[in] password Mật khẩu mới.
 * @return true nếu đăng ký thành công, false nếu thất bại.
 */
bool Account::registerAccount(vector<Account> &accountList, const string &username, const string &password) 
{
    if (accountExists(accountList, username))
    {
        cout << "Tài khoản đã tồn tại!\n";
        return false;
    }

    Account newAccount(username, password);
    accountList.emplace_back(newAccount);
    return true; // Đăng ký thành công
}


/**
 * @brief Đăng nhập vào hệ thống.
 * @param[in] accountList Danh sách tài khoản hiện có.
 * @param[in] username Tên tài khoản cần đăng nhập.
 * @param[in] password Mật khẩu cần xác thực.
 * @return true nếu đăng nhập thành công, false nếu thất bại.
 */
bool Account::login(const vector<Account>& accountList, const string& username, const string& password) 
{
    for (const auto &acc : accountList) 
    {
        if (acc.getUsername() == username && acc.getPassword() == password) return true; // Đăng nhập thành công
    }
    return false; // Đăng nhập thất bại
}


/**
 * @brief Xác thực tài khoản của Manager.
 * @param[in] password Mật khẩu cần kiểm tra.
 * @return true nếu đúng mật khẩu của Manager, false nếu không.
 */
bool Account::VerifyManagerAccount(const string& password)
{
    return accountList.begin()->getPassword() == password;
}


/**
 * @brief Xác thực tài khoản của Manager.
 * @param[in] password Mật khẩu cần kiểm tra.
 * @return true nếu đúng mật khẩu của Manager, false nếu không.
 */
void Account::showListAccount()
{
    for (const auto &acc : accountList)
    {
        cout << "user_name: " << acc.getUsername() << "\tpassword: " << acc.getPassword() << endl;
    }
}