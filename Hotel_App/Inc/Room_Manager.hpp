/********************************************************
 * @file    Room_Manager.hpp
 * @brief   Quản lý danh sách phòng trống, phòng đã đặt.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef ROOM_MANAGER_HPP
#define ROOM_MANAGER_HPP

#include "Room.hpp"
#include "Guess_Employee.hpp"
#include "UI.hpp"
#include <vector>

/** @def SUCCESS
 *  @brief Giá trị thành công của một thao tác.
 */
#define SUCCESS 1


/** @def FAIL
 *  @brief Giá trị thất bại của một thao tác.
 */
#define FAIL 0


/** @def EXIST
 *  @brief Trạng thái phòng đã tồn tại.
 */
#define EXIST 0


/** @def NOT_EXIST
 *  @brief Trạng thái phòng chưa tồn tại.
 */
#define NOT_EXIST 1


/**
 * @class RoomManager
 * @brief Lớp xây dựng các tính năng quản lý phòng sử dụng bởi quản lý.
 */
class RoomManager
{
    private:
        /**
         * @brief Tìm thông tin khách thuê dựa trên số phòng.
         * @param[in] room Số phòng cần tìm.
         * @return Con trỏ đến đối tượng `Guess` nếu tìm thấy, nullptr nếu không.
         */
        Guess* findguessbyRoom(const int &room);


        /**
         * @brief Kích hoạt hoặc vô hiệu hóa phòng.
         * @param[in] room Số phòng cần thay đổi trạng thái.
         * @param[in] Action Hành động cần thực hiện (true = kích hoạt, false = vô hiệu hóa).
         */
        void Activate_Deactivate(const int &room, bool Action);


        /**
         * @brief Xóa phòng khỏi danh sách phòng có sẵn.
         * @param[in] room Số phòng cần xóa.
         * @return true nếu xóa thành công, false nếu không thể xóa.
         */
        bool EraseAvailableRoom(const int &room);

    public:
        /**
         * @brief Constructor khởi tạo danh sách phòng của khách sạn ở trạng thái chưa sẵn sàng.
         */
        RoomManager();


        /**
         * @brief Kiểm tra xem phòng đã tồn tại trong danh sách phòng sẵn có hay chưa.
         * @param[in] room_number Số phòng cần kiểm tra.
         * @return true nếu phòng tồn tại, false nếu không.
         */
        static bool IsRoomAvailableExist(const int &room_number);


        /**
         * @brief Kiểm tra xem phòng có tồn tại trong danh sách mặc định hay không.
         * @param[in] room_number Số phòng cần kiểm tra.
         * @return true nếu phòng tồn tại, false nếu không.
         */
        bool IsRoomDefaultExist(const int &room_number);


        /**
         * @brief Thêm phòng mới vào hệ thống.
         * @param[in] number Số phòng cần thêm.
         * @return true nếu thêm thành công, false nếu thất bại.
         */
        bool AddRoom(const int &number);


        /**
         * @brief Xóa phòng khỏi hệ thống.
         * @param[in] number Số phòng cần xóa.
         */
        void deleteRoom(const int &number);


        /**
         * @brief Lấy thông tin chi tiết về phòng.
         * @param[in] room Số phòng cần xem thông tin.
         * @return true nếu tìm thấy thông tin phòng, false nếu không có dữ liệu.
         */
        bool RoomInfo(const int &room);


        /**
         * @brief Hiển thị danh sách phòng trong hệ thống.
         */
        void ShowListRoomDefault();
};

/** 
 * @var list_room_available
 * @brief Danh sách toàn cục chứa thông tin các phòng sẵn có.
 */
extern std::vector<Room> list_room_available;

#endif  // ROOM_MANAGER_HPP
