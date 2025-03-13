/********************************************************
 * @file    Service.hpp
 * @brief   Quản lý trạng thái dịch vụ trong hệ thống.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef SERVICE_HPP
#define SERVICE_HPP

#include "Std_Types.hpp"

/**
 * @enum service_option
 * @brief Lưu trữ các loại dịch vụ mà hệ thống hỗ trợ.
 */
typedef enum
{
    NONE_SERVICE,   /**< Không sử dụng dịch vụ */
    GYM,           /**< Dịch vụ phòng gym */
    BIRTHDAY_PARTY, /**< Dịch vụ tổ chức sinh nhật */
    CAR_RENT,      /**< Dịch vụ cho thuê xe */
    PET_CARE,      /**< Dịch vụ chăm sóc thú cưng */
    FOOD_ORDER,    /**< Dịch vụ đặt đồ ăn */
    SPA_MASSAGE,   /**< Dịch vụ spa và massage */
    TOTAL_SERVICE  /**< Tổng số dịch vụ hỗ trợ */
} service_option;


/**
 * @typedef service_dtype
 * @brief Kiểu dữ liệu lưu trữ dịch vụ và giá của chúng.
 */
typedef std::map<service_option, int> service_dtype;


/**
 * @class Service
 * @brief Lớp quản lý trạng thái và thông tin dịch vụ.
 */
class Service
{
    private:
        service_dtype service; /**< Danh sách dịch vụ và giá của chúng */

    public:
        /**
         * @brief Constructor khởi tạo một dịch vụ mới.
         * @param[in] option Tùy chọn dịch vụ.
         * @param[in] price Giá của dịch vụ.
         */
        Service(const service_option &option, const int &price)
        {
            service[option] = price;
        }


        /**
         * @brief Lấy thông tin về dịch vụ.
         * @return service_dtype - Dữ liệu của dịch vụ (loại dịch vụ và giá).
         */
        service_dtype getService() const { return service; }


        /**
         * @brief Xóa một dịch vụ khỏi danh sách.
         * @param[in] option Dịch vụ cần xóa.
         */
        void deleteService(const service_option &option)
        {
            if (service.find(option) != service.end()) service.erase(option);
        }
};

#endif  // SERVICE_HPP
