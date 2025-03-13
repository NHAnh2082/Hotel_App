/********************************************************
 * @file    Guess.hpp
 * @brief   Quản lý thông tin khách hàng thuê phòng.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef GUESS_HPP
#define GUESS_HPP

#include "Std_Types.hpp"

/**
 * @enum feedback_selection
 * @brief Liệt kê các định dạng phản hồi của khách hàng.
 */
typedef enum
{
    NONE_FEEDBACK, /**< Không có phản hồi */
    NEGATIVE,      /**< Phản hồi tiêu cực */
    POSITIVE,      /**< Phản hồi tích cực */
    TOTAL_FEEDBACK /**< Tổng số loại phản hồi */
} feedback_selection;


/**
 * @typedef Feedback
 * @brief Kiểu dữ liệu để lưu trữ phản hồi của khách hàng.
 */
typedef map<feedback_selection, string> Feedback;

/**
 * @class Guess
 * @brief Lớp lưu trữ thông tin khách thuê phòng.
 */
class Guess
{
    private:
        int room;                   /**< Số phòng khách thuê */
        string name;                /**< Tên khách hàng */
        string phone;               /**< Số điện thoại khách */
        string checkin;             /**< Ngày check-in */
        string checkout;            /**< Ngày check-out */
        Feedback guess_feedback;    /**< Phản hồi từ khách hàng */
        string guess_service;   /**< Dịch vụ khách hàng đã sử dụng */

    public:
        /**
         * @brief Constructor khởi tạo thông tin khách thuê phòng.
         * @param[in] room Số phòng khách thuê.
         * @param[in] name Tên khách hàng.
         * @param[in] phone Số điện thoại khách hàng.
         * @param[in] checkin Ngày check-in của khách hàng.
         */
        Guess(const int &room, const string &name, const string &phone, const string &checkin)  
            : room(room), name(name), phone(phone), checkin(checkin)
        {
            guess_feedback[NONE_FEEDBACK] = "chưa có đánh giá";
            checkout = "không có thông tin";
        } 

        /**
         * @brief Cập nhật ngày check-out của khách hàng.
         * @param[in] guess_checkout Ngày check-out mới.
         */
        void setCheckOut(string &guess_checkout) { checkout = guess_checkout; }

        /**
         * @brief Cập nhật dịch vụ mà khách hàng đã sử dụng.
         * @param[in] name_service Tên dịch vụ khách hàng sử dụng.
         */
        void setService(string name_service) { guess_service = name_service; }

        /**
         * @brief Cập nhật phản hồi của khách hàng.
         * @param[in] feedback Đối tượng `Feedback` chứa phản hồi của khách.
         */
        void setFeedback(Feedback feedback) { guess_feedback = feedback; }

        /**
         * @brief Lấy phản hồi của khách hàng.
         * @return Feedback - Phản hồi của khách hàng.
         */
        Feedback getFeedback() const { return guess_feedback; }

        /**
         * @brief Lấy thông tin dịch vụ khách hàng đã sử dụng.
         * @return std::string - Tên dịch vụ khách hàng sử dụng.
         */
        string getService() const { return guess_service; }

        /**
         * @brief Lấy tên khách hàng.
         * @return std::string - Tên khách hàng.
         */
        string getName() const { return name; }

        /**
         * @brief Lấy số điện thoại khách hàng.
         * @return std::string - Số điện thoại khách hàng.
         */
        string getPhone() const { return phone; }

        /**
         * @brief Lấy ngày check-in của khách hàng.
         * @return std::string - Ngày check-in.
         */
        string getCheckin() const { return checkin; }

        /**
         * @brief Lấy ngày check-out của khách hàng.
         * @return std::string - Ngày check-out.
         */
        string getCheckout() const { return checkout; }

        /**
         * @brief Lấy số phòng mà khách hàng đã thuê.
         * @return int - Số phòng khách thuê.
         */
        int getRoom() const { return room; }
};

#endif  // GUESS_HPP
