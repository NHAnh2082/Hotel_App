#include "..\\Inc\\Guess_Employee.hpp"

// Danh sách chứa thông tin khách thuê phòng
vector<Guess> list_guess;


// Danh sách một số feedback chưa tốt
vector<string> Negative_content = 
{
    "Cần cải thiện tốc độ xử lý thanh toán.",
    "Dịch vụ tạm ổn, không có gì đặc biệt. ",
    "Phải chờ đợi quá lâu mới được phục vụ.",
};


// Danh sách các feedback tốt
vector<string> Positve_content = 
{
    "Nhân viên rất thân thiện.",
    "Nhà tắm sạch sẽ, ngăn náp.",
    "Bữa ăn được phục vụ đa dạng, nhiều món."
};


/**
 * @brief Tìm thông tin phòng dựa trên số điện thoại của khách.
 * @param[in] phone Số điện thoại khách.
 * @return Con trỏ đến đối tượng `Guess` nếu tìm thấy, nullptr nếu không.
 */
Guess* GuessEmployee::findRoombyPhone(const string &phone)
{
    for (auto& guess : list_guess)       // Duyệt danh sách khách
    {    
        if (guess.getPhone() == phone)   // Kiểm tra SDT có trùng khớp hay không
        {
            return &guess;               // Trả về thông tin của khách hàng
        }
    }
    return NULL;
}


/**
 * @brief Sinh ngẫu nhiên phản hồi của khách.
 * @return Feedback - Phản hồi của khách.
 */
Feedback GuessEmployee::GenerateRandomFeedback()
{
    srand(time(0));

    // Chọn ngẫu nhiên loại phản hồi (Negative/Positive)
    feedback_selection type = static_cast<feedback_selection>(rand() % TOTAL_FEEDBACK); 

    // Chọn ngẫu nhiên các số từ 0 - 2 để truy xuất mô tả phản hồi tương ứng trong danh sách 
    int content = rand() % 3;   
    
    // Kết quả phản hồi
    Feedback feedback_result;
    
    switch(type)
    {
        case POSITIVE:
            feedback_result[POSITIVE] = Positve_content[content];
            break;

        case NEGATIVE:
            feedback_result[NEGATIVE] = Negative_content[content];
            break;

        case NONE_FEEDBACK:
            feedback_result[NONE_FEEDBACK] = "Không ý kiến";
            break;

        default:
            break;
    }
    return feedback_result; 
}


/**
 * @brief Sinh ngẫu nhiên dịch vụ mà khách đã sử dụng.
 * @return std::string - Dịch vụ ngẫu nhiên mà khách sử dụng.
 */
string GuessEmployee:: GenerateRandomService()
{
    srand(time(0));

    // Chọn ngẫu nhiên loại dịch vụ
    service_option number = static_cast<service_option>(rand() % TOTAL_SERVICE);

    // Mô tả dịch vụ tương ứng
    return service_description[number]; 
}


/**
 * @brief Xóa thông tin khách khi họ trả phòng.
 * @param[in] room Số phòng cần xóa thông tin khách.
 */
void GuessEmployee::EraseGuessInfo(const int &room)
{
    int count = 0;

    // Duyệt qua danh sách khách hàng
    for(auto &guess : list_guess)
    {
        // Nếu phòng muốn kiểm tra trùng với dữ liệu của khách thì xóa thông tin của khách khỏi danh sách
        if (guess.getRoom() == room)
        {
            list_guess.erase(list_guess.begin() + count);
            break;
        }
        count++;
    }
}


/**
 * @brief Hiển thị thông tin phản hồi dịch vụ của khách.
 * @param[in] guess Đối tượng `Guess` chứa thông tin khách.
 */
void GuessEmployee::ServiceFeedbackInfo(const Guess& guess)
{

    //lambda để tạo số ngẫu nhiên cho số lượng sử dụng dịch vụ
    auto GenerateRandomnumber = []()
    {
        srand(time(0));
        int total = 0;
        while(total == 0){
          total = rand() % 10;
        };
        return total;
    };

    //lambda để tách chuỗi và tính ra số ngày ở khách sạn
    auto totalday = [](const string& checkin,const string& checkout)
    {
        int start_day = 0,end_day = 0;
        int i = 0; 

        while(checkin[i - 3] != '-')
        {
            if(checkin[i - 1] == '-' || checkin[i - 2] == '-')
            {
                start_day*= 10;                 //xử lý trường hợp khi giá trị cần chuyển đổi từ giá trị chục trở lên
                char index = checkin[i] - '0';  //chuyển đổi ký tự số sang dạng integer
                start_day+=index;               //cập nhật giá trị chuyển đổi 
            }
            i++;
        }
        i = 0;

        while(checkout[i - 3] != '-')
        {
            if(checkout[i - 1] == '-' || checkout[i - 2] == '-')
            {
                end_day*= 10;
                char index = checkout[i] - '0';
                end_day+=index;
            }
            i++;
        }
        return end_day - start_day;
    };

    //lambda để lấy giá dịch vụ
    auto getPrice = [guess]()
    {
         for(auto& service : list_service)
         {
            for(auto& service_ : service.getService())
            {
                if(service_.first == GYM && (guess.getService()) == service_description[1]) return service_.second;
                else if(service_.first == BIRTHDAY_PARTY && (guess.getService()) == service_description[2]) return service_.second;
                else if(service_.first == CAR_RENT && (guess.getService()) == service_description[3]) return service_.second;
                else if(service_.first == PET_CARE && (guess.getService()) == service_description[4]) return service_.second;
                else if(service_.first == FOOD_ORDER && (guess.getService()) == service_description[5]) return service_.second;
                else if(service_.first == SPA_MASSAGE && (guess.getService()) == service_description[6]) return service_.second;
                else return service_.second;
            }
        }
        return 0;
    };

    int price = getPrice();
    int quantity = GenerateRandomnumber();
    int raw_cost = price * quantity;
    int final_cost = ((raw_cost * 0.1) + raw_cost);
    int day_count =  totalday(guess.getCheckin(),guess.getCheckout());
    auto service_description = [guess]()
    {
        for(auto feedback : guess.getFeedback()) return feedback.second;
        return string("không sử dụng dịch vụ");
    };

    UI::showMessage("dịch vụ sử dụng");
    UI::showMessage("Tên\t\t\tĐơn giá\t\t\tsố lượng");
    UI::showMessage(guess.getService() + "\t\t|" + to_string(price) + "\t\t\t|" +  to_string(quantity));
    UI::showMessage("Thời gian ở: " + to_string(day_count));
    UI::showMessage("Tổng chi phí dịch vụ: " + to_string(raw_cost) + " $");
    UI::showMessage("Thuế VAT: 10%");
    UI::showMessage("feedback: " + service_description());    
    UI::showMessage("Thành tiền: " + to_string(final_cost) + " $");
}


/**
 * @brief Lấy thông tin khách hàng dựa trên số điện thoại.
 * @param[in] phone Số điện thoại của khách.
 * @return Con trỏ đến đối tượng `Guess` nếu tìm thấy, nullptr nếu không.
 */
Guess* GuessEmployee::GuessInfo(const string &phone)
{
    Guess* guess = findRoombyPhone(phone);

    if (guess != NULL)
    {
        UI::showMessage("Thông tin khách");
        UI::showMessage("Tên: " + guess->getName());
        UI::showMessage("SDT: " + guess->getPhone());
        UI::showMessage("Phòng ở: " + to_string(guess->getRoom()));
        UI::showMessage("Thời gian checkIn: " + guess->getCheckin());
        guess->setFeedback(GenerateRandomFeedback()); // Trả về phản hồi của khách hàng
        guess->setService(GenerateRandomService());   // Trả về dịch vụ mà khách hàng đã sử dụng
        return guess;
    }
    return NULL;
}


/**
 * @brief Đặt phòng cho khách.
 * @param[in] number Số phòng cần đặt.
 * @param[in] name Tên khách hàng.
 * @param[in] phone Số điện thoại của khách.
 * @param[in] checkin Ngày check-in của khách.
 * @return true nếu đặt phòng thành công, false nếu thất bại.
 */
bool GuessEmployee::BookRoom(const int &room_book, const string &name, const string &phone, const string &checkin)
{
    // Duyệt qua từng phòng đã thêm bởi manager
    for (auto &room : list_room_available)
    {
        // Trích xuất dữ liệu của phòng hiện tại
        for (auto &room_avaliable : room.getRoomAvailable())
        {
            if (room_avaliable.first == room_book && room_avaliable.second == Reserved)
            { 
                return FAIL; 
            }
            else if(room_avaliable.first == room_book && room_avaliable.second == Empty)
            {
                // Kiểm tra phòng muốn đặt đã có khách thuê trước đó chưa, nếu có thì xóa thông tin khách cũ
                EraseGuessInfo(room_book);

                // Thêm thông tin khách mới
                list_guess.emplace_back(room_book, name, phone, checkin);

                // Cập nhật trạng thái phòng -> đặt phòng
                room.CheckInRoom(room_book);
                
                return SUCCESS;
            }    
        }
    }   
    return 0;    
}


/**
 * @brief Hủy đặt phòng của khách.
 * @param[in] guess Đối tượng `Guess` chứa thông tin khách.
 * @param[in] checkout Ngày trả phòng của khách.
 */
void GuessEmployee::UnbookRoom(Guess &guess, string &checkout)
{
    // Cài đặt ngày trả phòng
    guess.setCheckOut(checkout);
    
    //duyệt qua từng phòng đã thêm bởi manager
    for(auto &room : list_room_available)
    {
        // Trích xuất dữ liệu của phòng hiện tại
        for (auto &room_ : room.getRoomAvailable())
        {
            if (room_.first == guess.getRoom()) // xử lý nếu tìm thấy phòng cần trả trong danh sách 
            { 
                //cập nhật trạng thái phòng -> trả phòng
                room.CheckOutRoom(guess.getRoom());
            }
        } 
    }
}


/**
 * @brief Hiển thị danh sách khách đã thuê phòng.
 * @return true nếu có khách, false nếu không có khách.
 */
bool GuessEmployee::ShowListGuess()
{
    if (list_guess.empty())
    {
        UI::showMessage("Không có khách thuê nào.");
        return FAIL;
    }

    for(auto &guess : list_guess)
    {
        UI::showMessage("Phòng: " + to_string(guess.getRoom()) + 
                        ", Tên: " + guess.getName() + 
                        ", SDT: " + guess.getPhone() + 
                        ", checkin: " + guess.getCheckin() + 
                        ", checkout: " + guess.getCheckout());
    }
    return SUCCESS;
}


/**
 * @brief Hiển thị danh sách phòng còn trống.
 * @return true nếu có phòng trống, false nếu không có.
 */
bool GuessEmployee::ShowListRoomAvailable()
{
    // Kiểm tra danh sách phòng được thêm bởi manager có rỗng hay không
    if (list_room_available.empty()) return FAIL;

    int floor = 1;

    // lambda trả về kết quả chuyển đổi sang ký tự tương ứng trạng thái phòng hiện tại
    auto status = [](available_roomstatus &st){ return st == Reserved ? 'X' : 'O'; };

    // lambda trả về kết quả phòng cuối cùng
    auto final_room = [=]()
    {
        auto it = list_room_available.back();

        for (auto value : it.getRoomAvailable())
        {
            return value.first;
        }
        return 0;
    };
    
    // in ra tầng đầu tiên
    UI::showMessage("floor " + to_string(floor));

    // duyệt qua từng phòng 
    for(size_t i=0; i<list_room_available.size(); i++)
    {
        bool update_floor = false;
        room_number current = 0, next = 0;   // lưa số phòng hiện tại và kế tiếp 
        available_roomstatus st;             // trạng thái của phòng 
       
        // trích xuất ra số thứ tự và trạng thái của phòng hiện tại 
        for(auto &room_available : list_room_available[i].getRoomAvailable())
        {
            current = room_available.first;
            st = room_available.second;
        }

        // trích xuất dữ liệu phòng tiếp theo cho đến khi gặp phòng cuối cùng
        if (current != final_room())
        {
            for(auto &room_available : list_room_available[i+1].getRoomAvailable()) next = room_available.first;
        }

        if ((next - current) > 5)
        {
            UI::showMessage("\t" + to_string(current) + "(" + status(st) + ")");   // in ra tâng phòng cuối của tầng hiện tại
            UI::showMessage("\nfloor " + to_string(++floor));    
            update_floor = true;    
        }

        // in ra số thứ tự và trạng thái của các phòng trên 1 tầng
        if (!update_floor || current == final_room())
        {
            cout << "\t" << to_string(current) << "(" << status(st) << ")" << "\t";
        }
    }

    cout << endl;
    return SUCCESS;
}