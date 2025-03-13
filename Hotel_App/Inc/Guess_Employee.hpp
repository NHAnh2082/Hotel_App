/********************************************************
 * @file    Guess_Employee.hpp
 * @brief   Quản lý khách thuê phòng, đặt phòng, hủy phòng.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef GUESSE_EMPLOYEE_HPP
#define GUESSE_EMPLOYEE_HPP

#include "Guess.hpp"
#include "Room_Manager.hpp"
#include "Service_Manager.hpp"
#include "UI.hpp"
#include <ctime>


/**
 * @class GuessEmployee
 * @brief Lớp quản lý khách thuê phòng, đặt phòng, hủy phòng và phản hồi dịch vụ.
 */
class GuessEmployee
{
    private:
        /**
         * @brief Tìm thông tin phòng dựa trên số điện thoại của khách.
         * @param[in] phone Số điện thoại khách.
         * @return Con trỏ đến đối tượng `Guess` nếu tìm thấy, nullptr nếu không.
         */
        Guess *findRoombyPhone(const string &phone);

        /**
         * @brief Sinh ngẫu nhiên phản hồi của khách.
         * @return Feedback - Phản hồi của khách.
         */
        Feedback GenerateRandomFeedback();

        /**
         * @brief Sinh ngẫu nhiên dịch vụ mà khách đã sử dụng.
         * @return std::string - Dịch vụ ngẫu nhiên mà khách sử dụng.
         */
        std::string GenerateRandomService();

        /**
         * @brief Xóa thông tin khách khi họ trả phòng.
         * @param[in] room Số phòng cần xóa thông tin khách.
         */
        void EraseGuessInfo(const int &room);

    public:
        /**
         * @brief Hiển thị thông tin phản hồi dịch vụ của khách.
         * @param[in] guess Đối tượng `Guess` chứa thông tin khách.
         */
        void ServiceFeedbackInfo(const Guess &guess);

        /**
         * @brief Lấy thông tin khách hàng dựa trên số điện thoại.
         * @param[in] phone Số điện thoại của khách.
         * @return Con trỏ đến đối tượng `Guess` nếu tìm thấy, nullptr nếu không.
         */
        Guess *GuessInfo(const string &phone);

        /**
         * @brief Đặt phòng cho khách.
         * @param[in] number Số phòng cần đặt.
         * @param[in] name Tên khách hàng.
         * @param[in] phone Số điện thoại của khách.
         * @param[in] checkin Ngày check-in của khách.
         * @return true nếu đặt phòng thành công, false nếu thất bại.
         */
        bool BookRoom(const int &number, const string &name, const string &phone, const string &checkin);

        /**
         * @brief Hủy đặt phòng của khách.
         * @param[in] guess Đối tượng `Guess` chứa thông tin khách.
         * @param[in] checkout Ngày trả phòng của khách.
         */
        void UnbookRoom(Guess &guess, string &checkout);

        /**
         * @brief Hiển thị danh sách khách đã thuê phòng.
         * @return true nếu có khách, false nếu không có khách.
         */
        bool ShowListGuess();

        /**
         * @brief Hiển thị danh sách phòng còn trống.
         * @return true nếu có phòng trống, false nếu không có.
         */
        bool ShowListRoomAvailable();

        /**
         * @brief Kiểm tra xem phòng có còn trống hay không.
         * @param[in] room_number Số phòng cần kiểm tra.
         * @return true nếu phòng còn trống, false nếu đã được đặt.
         */
        bool IsRoomAvailable(int room_number);
};

/** 
 * @var list_guess
 * @brief Danh sách toàn cục chứa thông tin các khách thuê phòng.
 */
extern vector<Guess> list_guess; // danh sách thông tin khách (toàn cục)

#endif  // GUESSE_EMPLOYEE_HPP
 