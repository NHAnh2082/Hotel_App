/********************************************************
 * @file    Service_Manager.hpp
 * @brief   Quản lý danh sách dịch vụ trong hệ thống.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef SERVICE_MANAGER_HPP
#define SERVICE_MANAGER_HPP

#include "Service.hpp"
#include "UI.hpp"
#include <iomanip>

/** @def SERVICE_EXIST
 *  @brief Giá trị đại diện cho trạng thái dịch vụ đã tồn tại.
 */
#define SERVICE_EXIST 0


/** @def SERVICE_NOT_EXIST
 *  @brief Giá trị đại diện cho trạng thái dịch vụ chưa tồn tại.
 */
#define SERVICE_NOT_EXIST 1


/**
 * @class ServiceManager
 * @brief Lớp quản lý danh sách dịch vụ trong hệ thống.
 */
class ServiceManager
{
    private:
        /**
         * @brief Kiểm tra xem dịch vụ có tồn tại trong hệ thống hay không.
         * @param[in] name_service Tùy chọn dịch vụ cần kiểm tra.
         * @return true nếu dịch vụ tồn tại, false nếu không.
         */
        bool IsServiceExist(const service_option &name_service);

    public:
        /**
         * @brief Thêm dịch vụ mới vào hệ thống.
         * @param[in] service_number Số thứ tự của dịch vụ.
         * @param[in] price Giá dịch vụ.
         * @return true nếu thêm thành công, false nếu thất bại.
         */
        bool AddService(const int &service_number, const int &price);


        /**
         * @brief Xóa một dịch vụ khỏi hệ thống.
         * @param[in] name_service Số thứ tự của dịch vụ cần xóa.
         * @return true nếu xóa thành công, false nếu thất bại.
         */
        bool deleteService(const int &name_service);

        
        /**
         * @brief Hiển thị danh sách tất cả các dịch vụ hiện có.
         * @return true nếu có dịch vụ trong hệ thống, false nếu không có.
         */
        bool ShowListService();
};

/** 
 * @var list_service
 * @brief Danh sách toàn cục chứa thông tin các dịch vụ trong hệ thống.
 */
extern vector<Service> list_service;

/** 
 * @var service_description
 * @brief Danh sách mô tả các dịch vụ.
 */
extern vector<string> service_description;

#endif  // SERVICE_MANAGER_HPP
