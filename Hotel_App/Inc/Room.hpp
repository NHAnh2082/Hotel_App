/********************************************************
 * @file    Room.hpp
 * @brief   Quản lý trạng thái phòng.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef ROOM_HPP
#define ROOM_HPP

#include <map>

/**
 * @enum default_room_status
 * @brief Định dạng trạng thái của phòng khi khởi tạo ban đầu.
 */
typedef enum
{
    Unavailable, /**< Phòng chưa được thêm vào danh sách hoạt động */
    Available    /**< Phòng đã được thêm vào danh sách hoạt động */
} default_room_status;


/**
 * @enum available_roomstatus
 * @brief Định dạng trạng thái của các phòng đã thêm vào danh sách hoạt động.
 */
typedef enum
{
    Empty,    /**< Phòng còn trống */
    Reserved  /**< Phòng đã được đặt trước */
} available_roomstatus;


/**
 * @typedef room_number
 * @brief Kiểu dữ liệu đại diện cho số phòng.
 */
typedef int room_number;


/**
 * @typedef room_available_dtype
 * @brief Định nghĩa kiểu dữ liệu cho danh sách phòng đã được thêm vào hệ thống.
 */
typedef std::map<room_number, available_roomstatus> room_available_dtype;


/**
 * @typedef room_default_dtype
 * @brief Định nghĩa kiểu dữ liệu cho danh sách phòng mặc định khi khởi tạo hệ thống.
 */
typedef std::map<room_number, default_room_status> room_default_dtype;


/**
 * @class Room
 * @brief Lớp quản lý trạng thái của phòng.
 */
class Room
{
    private:
        room_available_dtype room_available; /**< Danh sách phòng đã được thêm vào hệ thống */
        room_default_dtype room_default;     /**< Danh sách phòng mặc định khi khởi tạo */

    public:
        /**
         * @brief Constructor khởi tạo đối tượng `Room`.
         * @param[in] room_available Danh sách phòng đã được thêm vào hệ thống.
         */
        Room(const room_available_dtype &room_available) : room_available(room_available) {}


        /**
         * @brief Lấy danh sách phòng đã được thêm vào hệ thống.
         * @return room_available_dtype - Danh sách phòng đã thêm.
         */
        room_available_dtype getRoomAvailable() const { return room_available; }


        /**
         * @brief Đánh dấu phòng là đã được đặt (Reserved).
         * @param[in] number Số phòng cần cập nhật trạng thái.
         */
        void CheckInRoom(const int &number) { room_available[number] = Reserved; }


        /**
         * @brief Đánh dấu phòng là trống (Empty).
         * @param[in] number Số phòng cần cập nhật trạng thái.
         */
        void CheckOutRoom(const int &number) { room_available[number] = Empty; }
};

#endif  // ROOM_HPP
