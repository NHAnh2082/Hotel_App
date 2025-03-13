#include "..\\Inc\\UI.hpp"

/**
 * @brief Lấy lựa chọn từ người dùng dưới dạng số nguyên.
 * @param[in] prompt Thông điệp hiển thị cho người dùng.
 * @return int - Giá trị người dùng nhập vào.
 */
int UI::getUserChoice(const string& prompt) 
{
    int choice;
    cout << prompt;
    cin >> choice;
    return choice;
}


/**
 * @brief Lấy lựa chọn từ người dùng dưới dạng số thực.
 * @param[in] prompt Thông điệp hiển thị cho người dùng.
 * @return float - Giá trị số thực người dùng nhập vào.
 */
float UI::getUserChoiceFloat(const string& prompt) 
{
    float choice;
    cout << prompt;
    cin >> choice;
    return choice;
}


/**
 * @brief Hiển thị thông báo đến người dùng.
 * @param[in] message Chuỗi thông báo cần hiển thị.
 */
void UI::showMessage(const string& message) 
{
    cout << message << endl;
}


/**
 * @brief Lấy chuỗi dữ liệu nhập từ người dùng.
 * @param[in] prompt Thông điệp hiển thị cho người dùng.
 * @return std::string - Chuỗi nhập vào từ người dùng.
 */
string UI::getInputString(const string& prompt) 
{
    string input;
    cout << prompt;
    cin >> input;
    return input;
}