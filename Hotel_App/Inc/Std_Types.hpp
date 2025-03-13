/********************************************************
 * @file    Std_Types.hpp
 * @brief   Khai báo các thư viện và định nghĩa các kiểu dữ liệu chuẩn 
 *          dùng chung trong project.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef STD_TYPES_HPP
#define STD_TYPES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <initializer_list>
#include <functional>

/** 
 * @namespace std
 * @brief Sử dụng không gian tên chuẩn để tránh lỗi biên dịch.
 */
using namespace std;

/** @def FAIL
 *  @brief Định nghĩa trạng thái thất bại.
 */
#ifndef FAIL
#define FAIL 0
#endif  // FAIL

/** @def SUCCESS
 *  @brief Định nghĩa trạng thái thành công.
 */
#ifndef SUCCESS
#define SUCCESS 1
#endif  // SUCCESS

#endif  // STD_TYPES_HPP
