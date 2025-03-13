/********************************************************
 * @file    Menu_Item.hpp
 * @brief   Tạo từng mục trong Menu.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include "Std_Types.hpp"
#include <functional>

/**
 * @class MenuItem
 * @brief Lớp đại diện cho một mục trong menu.
 */
class MenuItem 
{
    private:
        int choice_;               /**< Số lựa chọn tương ứng với menu item */
        string description_;       /**< Mô tả của mục menu */
        function<void()> action_;  /**< Hàm thực thi khi mục menu được chọn */

    public:
        /**
         * @brief Constructor khởi tạo một mục menu.
         * @param[in] choice Số lựa chọn của mục menu.
         * @param[in] description Mô tả của mục menu.
         * @param[in] action Hàm thực thi khi mục menu được chọn.
         */
        MenuItem(int choice, const std::string &description, std::function<void()> action)
            : choice_(choice), description_(description), action_(action) {}


        /**
         * @brief Lấy số lựa chọn của mục menu.
         * @return int - Giá trị số của mục menu.
         */
        int getChoice() const 
        { 
            return choice_; 
        }


        /**
         * @brief Lấy mô tả của mục menu.
         * @return std::string - Mô tả của mục menu.
         */
        std::string getDescription() const 
        { 
            return description_; 
        }


        /**
         * @brief Thực thi hành động tương ứng với mục menu.
         */
        void executeAction() const 
        { 
            action_(); 
        }
};

#endif // MENU_ITEM_HPP
