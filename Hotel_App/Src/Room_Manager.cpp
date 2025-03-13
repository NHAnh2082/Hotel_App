#include "..\\Inc\\Room_Manager.hpp"

#define ACTIVATE   1
#define DEACTIVATE 0

vector<Room> list_room_available;                   // global used
vector<room_default_dtype> list_room_default;

/**
 * @brief Constructor khởi tạo danh sách phòng của khách sạn ở trạng thái chưa sẵn sàng.
 */
RoomManager::RoomManager()
{
    //mảng lưu só thứ tự các phòng mặc định ban đầu
    int room_initialized[] = 
    {
        101,102,103,104,105,
        201,202,203,204,205,
        301,302,303,304,305
    };

    //khởi tạo các phòng và trạng thái ban đầu
    for(auto& initialized : room_initialized)
    {
        room_default_dtype new_room;
        new_room[initialized] = Unavailable;    
        list_room_default.push_back(new_room);
    }
}


/**
 * @brief Xóa phòng khỏi danh sách phòng có sẵn.
 * @param[in] room Số phòng cần xóa.
 * @return true nếu xóa thành công, false nếu không thể xóa.
 */
bool RoomManager::EraseAvailableRoom(const int& number)
{
    int count = 0;
    Guess* guess = findguessbyRoom(number);

    //kiểm tra phòng hiện tại có khách thuê hay không hoặc khách đã trả phòng chưa
    if(guess == NULL || guess->getCheckout() != "khong co thong tin")
    {
        for(auto& room_available : list_room_available)
        {
            for(auto& room : room_available.getRoomAvailable())
            {
                if(room.first == number)
                {
                    list_room_available.erase(list_room_available.begin() + count);
                    return SUCCESS;
                }
            }
            count++;
        }
    }
    return FAIL;
}


/**
 * @brief Kích hoạt hoặc vô hiệu hóa phòng.
 * @param[in] room Số phòng cần thay đổi trạng thái.
 * @param[in] Action Hành động cần thực hiện (true = kích hoạt, false = vô hiệu hóa).
 */
void RoomManager::Activate_Deactivate(const int& number,bool Action)
{
    //vô hiệu hóa hoặc kích hoạt phòng trên danh sách gốc 
    for(auto it = list_room_default.begin() ; it != list_room_default.end() ; it++)
    {
        for(auto& room : *it)
        {
            if(room.first == number)
            {
                room.second = (Action == DEACTIVATE) ? Unavailable : Available;
                break;
            }
        }
    }
}


/**
 * @brief Hiển thị danh sách phòng trong hệ thống.
 */
void RoomManager::ShowListRoomDefault()
{
    int floor = 1;

    //lambda trả về kết quả chuyển đổi sang ký tự tương ứng với trạng thái phòng
    auto status = [=](default_room_status st){ return st == Available ? 'A' : 'U'; };

    //lambda trả về kết quả phòng cuối cùng
    auto final_room = [=]()
    {
        auto it = list_room_default.back();
        for(auto value : it) return value.first;
        return 0;
    };

    //in ra tầng đầu tiên
    UI::showMessage("floor " + to_string(floor));

    //duyệt qua từng phòng 
    for(size_t i = 0 ; i < list_room_default.size() ; i++)
    {
        bool update_foor = false;           // reset trạng thái tầng 
        room_number current = 0,next = 0;   // lưa số phòng hiện tại và kế tiếp 
        default_room_status st;             // trạng thái của phòng 

        //trích xuất ra số thứ tự và trạng thái của phòng hiện tại 
        for(auto& room_default : list_room_default[i])
        {
            current =  room_default.first;
            st = room_default.second;
        }
        
        //trích xuất dữ liệu phòng tiếp theo cho đến khi gặp phòng cuối cùng
        if(current != final_room())
        {
            //trích xuất ra số thứ tự của phòng tiếp theo 
            for(auto& room_default : list_room_default[i+1]) next =  room_default.first;
        }
        
        //kiểm tra có phải phòng cuối cùng của tầng hiện tại
        if((next - current) > 1)
        {
            UI::showMessage("\t" + to_string(current) + "(" + status(st) + ")");    // in ra tâng phòng cuối của tầng hiện tại
            UI::showMessage("\nfloor " + to_string(++floor));                       // in ra tầng kế tiếp    
            update_foor = true;                                                     // cập nhật trạng thái đã sang tầng mới
        }

        //in ra số thứ tự và trạng thái của các phòng trên 1 tầng 
        if(!update_foor || current == final_room()) cout << "\t" << to_string(current) << "(" << status(st) << ")" << "\t";
    }
    cout << endl;
}


/**
 * @brief Tìm thông tin khách thuê dựa trên số phòng.
 * @param[in] room Số phòng cần tìm.
 * @return Con trỏ đến đối tượng `Guess` nếu tìm thấy, nullptr nếu không.
 */
Guess* RoomManager::findguessbyRoom(const int& room)
{
    for(auto& guess : list_guess)           // duyet qua tung khach trong danh sach
    {       
        if(guess.getRoom() == room)         // kiem tra so phong cua khach hien tai co giong voi so phong can tra cuu
        {     
            return &guess;                  // neu tim thay so phong tuong ung thi tra ve thong tin cua khach
        }
    }
    return NULL;
} 


/**
 * @brief Kiểm tra xem phòng đã tồn tại trong danh sách phòng sẵn có hay chưa.
 * @param[in] room_number Số phòng cần kiểm tra.
 * @return true nếu phòng tồn tại, false nếu không.
 */
bool RoomManager::IsRoomAvailableExist(const int& room_check)
{
    for (auto &room : list_room_available)
    {
        for (auto &room_ : room.getRoomAvailable())
        {
            if (room_.first == room_check) return EXIST;
        }
    }
    return NOT_EXIST;
}


/**
 * @brief Kiểm tra xem phòng có tồn tại trong danh sách mặc định hay không.
 * @param[in] room_number Số phòng cần kiểm tra.
 * @return true nếu phòng tồn tại, false nếu không.
 */
bool RoomManager::IsRoomDefaultExist(const int& number)
{
    for (auto &room : list_room_default)
    {
        for(auto& room_ : room)
        {
            if(room_.first == number) return EXIST;
        }
    }
    return NOT_EXIST;
}


/**
 * @brief Thêm phòng mới vào hệ thống.
 * @param[in] number Số phòng cần thêm.
 * @return true nếu thêm thành công, false nếu thất bại.
 */
bool RoomManager::AddRoom(const int& number)
{
    if(IsRoomAvailableExist(number) == EXIST)
    {
        return FAIL;
    }

    //tạo 1 phòng mới sẵn sàng sử dụng 
    room_available_dtype new_room;
    new_room[number] = Empty;

    //đưa phòng vào hoạt động
    Activate_Deactivate(number,ACTIVATE);

    //thêm vào danh sách phòng sẵn sàng sử dụng
    list_room_available.emplace_back(new_room);
    
    return SUCCESS;
}


/**
 * @brief Lấy thông tin chi tiết về phòng.
 * @param[in] room Số phòng cần xem thông tin.
 * @return true nếu tìm thấy thông tin phòng, false nếu không có dữ liệu.
 */
bool RoomManager::RoomInfo(const int& room)
{
    //tim thong tin cua khach dua tren phong
    Guess* guess = findguessbyRoom(room);

    //tra ve feedback cua khach o phong can truy xuat
    const auto& feedback = [](Guess& guess)
    {
        for(auto& feeback : guess.getFeedback()) return feeback.second;
        return string("chưa có phản hồi");
    };
    
    //neu tim thay khach o phong can tim thi in ra thong tin 
    if(guess != NULL)
    {
        UI::showMessage("thong tin khach");
        UI::showMessage("ten: " + guess->getName());
        UI::showMessage("sdt: " + guess->getPhone());
        UI::showMessage("lich su checkin - checkout");
        UI::showMessage("thoi gian\tcheckin/out");
        UI::showMessage(guess->getCheckin() + "\tcheckin");
        UI::showMessage(guess->getCheckout() + "\tcheckout");
        UI::showMessage("Feedback: " + feedback(*guess));
        UI::showMessage("--------------------------------------");
        return SUCCESS;
    }
    return FAIL;
}


/**
 * @brief Xóa phòng khỏi hệ thống.
 * @param[in] number Số phòng cần xóa.
 */
void RoomManager::deleteRoom(const int& number)
{
   // kiểm tra phòng đã thêm vào danh sách chưa
   if(list_room_available.empty())
   {
        UI::showMessage("chưa có phòng nào được thêm");
        return;
   }
   //xóa phòng ra khỏi danh sách sẵn sàng sử dụng
   if(EraseAvailableRoom(number) == FAIL)
   {
        UI::showMessage("Phòng đang có khách sử dụng");
   }
   
   //vô hiệu hóa phòng 
   Activate_Deactivate(number,DEACTIVATE);
   UI::showMessage("xóa phòng" + to_string(number) + " thành công");
}