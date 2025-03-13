#include "..\\Inc\\File_Handling.hpp"

// sử dụng lại biến này để khôi phục lại danh sách các phòng khởi tạo ban đầu với trạng thái là Unavailable/Available
extern vector<room_default_dtype> list_room_default;   

mutex guess_mutex;
mutex room_mutex;
mutex service_mutex;
mutex employee_mutex;
mutex file_mutex;  // Mutex bảo vệ file khi ghi


/**
 * @brief Lưu dữ liệu vào file CSV.
 * @param[in] path Đường dẫn đến file CSV.
 * @param[in] type Loại dữ liệu cần lưu.
 * @return true nếu lưu thành công, false nếu thất bại.
 */
bool File_Handle::SaveData(const string& path,Storage_dtype infotype)
{
    // ofstream file(path);
    // if (!file.is_open()) return false;

    // switch (infotype)
    // {
    //     case GUESS_CSV:
    //         if (list_guess.empty()) 
    //         {
    //             UI::showMessage("Không có thông tin khách");
    //             return false;
    //         } 
    //         SaveGuessInfo(file);
    //         break;

    //     case ROOM_CSV:
    //         if (list_room_available.empty()) 
    //         {
    //             UI::showMessage("Không có thông tin phòng");
    //             return false;
    //         }
    //         SaveRoomInfo(file);
    //         break;

    //     case SERVICE_CSV:
    //         if (list_service.empty()) 
    //         {
    //             UI::showMessage("Không có thông tin dịch vụ");
    //             return false;
    //         }
    //         SaveServiceInfo(file);
    //         break;

    //     case EMPLOYEE_CSV:
    //         if (list_employees.empty()) 
    //         {
    //             UI::showMessage("Không có thông tin nhân viên");
    //             return false;
    //         }
    //         SaveEmployeeInfo(file);
    //         break;

    //     default:
    //         return false;
    // }

    // file.close();
    // return true;

    ofstream file(path);
    if (!file.is_open()) return false;

    // Chạy lưu file trên luồng riêng biệt
    auto future = async(launch::async, [this, &file, infotype]() 
    {
        switch (infotype)
        {
            case GUESS_CSV:
                if (list_guess.empty()) return;
                SaveGuessInfo(file);
                break;

            case ROOM_CSV:
                if (list_room_available.empty()) return;
                SaveRoomInfo(file);
                break;

            case SERVICE_CSV:
                if (list_service.empty()) return;
                SaveServiceInfo(file);
                break;

            case EMPLOYEE_CSV:
                if (list_employees.empty()) return;
                SaveEmployeeInfo(file);
                break;

            default:
                return;
        }
    });

    future.get(); // Đợi luồng hoàn thành
    file.close();
    return true;
}


/**
 * @brief Lưu dữ liệu khách thuê vào file CSV.
 * @param[in] file Con trỏ file cần ghi.
 */
void File_Handle::SaveGuessInfo(ofstream &file)
{
    // file << "Số Phòng, Tên Khách, Số Điện Thoại, Ngày Đặt Phòng, Ngày Trả Phòng\n";
    // for (const auto &guest : list_guess)
    // {
    //     file << guest.getRoom() << ","
    //          << guest.getName() << ","
    //          << guest.getPhone() << ","
    //          << guest.getCheckin() << ","
    //          << guest.getCheckout() << "\n";
    // }

    file << "Số Phòng, Tên Khách, Số Điện Thoại, Ngày Đặt Phòng, Ngày Trả Phòng\n";

    vector<future<void>> futures;  // Danh sách các luồng lưu dữ liệu

    for (const auto &guest : list_guess)
    {
        futures.emplace_back(async(launch::async, [&file, &guest]() 
        {
            lock_guard<mutex> lock(file_mutex); // Đảm bảo không có xung đột ghi file
            file << guest.getRoom() << ","
                 << guest.getName() << ","
                 << guest.getPhone() << ","
                 << guest.getCheckin() << ","
                 << guest.getCheckout() << "\n";
        }));
    }

    for (auto &fut : futures) fut.get();  // Đợi tất cả luồng hoàn thành
}


/**
 * @brief Lưu dữ liệu phòng vào file CSV.
 * @param[in] file Con trỏ file cần ghi.
 */
void File_Handle::SaveRoomInfo(ofstream &file)
{
    // file << "Số phòng (Available), Trạng thái phòng (Reserved: 1, Empty: 0)\n";
    
    // for (const auto &room : list_room_available)
    // {
    //     for (const auto &data : room.getRoomAvailable())
    //     {
    //         file << data.first << "," << data.second << "\n";
    //     }
    // }

    file << "Số phòng (Available), Trạng thái phòng (Reserved: 1, Empty: 0)\n";

    vector<future<void>> futures;

    for (const auto &room : list_room_available)
    {
        for (const auto &data : room.getRoomAvailable())
        {
            futures.emplace_back(async(launch::async, [&file, data]() 
            {
                lock_guard<mutex> lock(file_mutex);
                file << data.first << "," << data.second << "\n";
            }));
        }
    }

    for (auto &fut : futures) fut.get();
}


/**
 * @brief Lưu dữ liệu dịch vụ vào file CSV.
 * @param[in] file Con trỏ file cần ghi.
 */
void File_Handle::SaveServiceInfo(ofstream &file)
{
    // file << "STT dịch vụ, Giá dịch vụ\n";

    // for (const auto &service : list_service)
    // {
    //     for (const auto &data : service.getService())
    //     {
    //         file << data.first << "," << data.second << "\n";
    //     }
    // }

    file << "STT dịch vụ, Giá dịch vụ\n";

    vector<future<void>> futures;

    for (const auto &service : list_service)
    {
        for (const auto &data : service.getService())
        {
            futures.emplace_back(async(launch::async, [&file, data]() 
            {
                lock_guard<mutex> lock(file_mutex);
                file << data.first << "," << data.second << "\n";
            }));
        }
    }

    for (auto &fut : futures) fut.get();
}


/**
 * @brief Lưu dữ liệu nhân viên vào file CSV.
 * @param[in] file Con trỏ file cần ghi.
 */
void File_Handle::SaveEmployeeInfo(ofstream &file)
{
    // auto getPassword = [](const string& phone) -> string 
    // {
    //     for (const auto& account : accountList)
    //     {
    //         if (account.getUsername() == phone)
    //         {
    //             return account.getPassword();
    //         }
    //     }
    //     return "chưa có mật khẩu";
    // };

    // file << "ID, Tên NV, SDT (user_name), Vị trí, Ca làm, Mật khẩu\n";

    // for (const auto &employee : list_employees)
    // {
    //     file << employee.getId() << ","
    //          << employee.getName() << ","
    //          << employee.getPhoneNumber() << ","
    //          << employee.getPosition() << ","
    //          << employee.getWorkShift() << ","
    //          << getPassword(employee.getPhoneNumber()) << "\n";
    // }

    file << "ID, Tên NV, SDT (user_name), Vị trí, Ca làm, Mật khẩu\n";

    auto getPassword = [](const string& phone) -> string 
    {
        for (const auto& account : accountList)
        {
            if (account.getUsername() == phone)
            {
                return account.getPassword();
            }
        }
        return "chưa có mật khẩu";
    };

    vector<future<void>> futures;

    for (const auto &employee : list_employees)
    {
        futures.emplace_back(std::async(launch::async, [&file, &employee, getPassword]() {
            lock_guard<mutex> lock(file_mutex);
            file << employee.getId() << ","
                 << employee.getName() << ","
                 << employee.getPhoneNumber() << ","
                 << employee.getPosition() << ","
                 << employee.getWorkShift() << ","
                 << getPassword(employee.getPhoneNumber()) << "\n";
        }));
    }

    for (auto &fut : futures) fut.get();
}


/**
 * @brief Đọc dữ liệu từ file CSV.
 * @param[in] path Đường dẫn đến file CSV.
 * @param[in] type Loại dữ liệu cần đọc.
 * @return FILE_NOT_EMPTY nếu file có dữ liệu, FILE_EMPTY nếu file rỗng, false nếu thất bại.
 */
int File_Handle::LogData(const string& path, Storage_dtype infotype)
{
    // ifstream file(path);
    // if (!file.is_open()) return false;

    // string line;
    // if (!getline(file, line)) return FILE_EMPTY;    // Bỏ qua tiêu đề

    // while (getline(file, line))
    // {
    //     switch (infotype)
    //     {
    //         case GUESS_CSV: LogGuessInfo(line); break;
    //         case ROOM_CSV: LogRoomInfo(line); break;
    //         case SERVICE_CSV: LogServiceInfo(line); break;
    //         case EMPLOYEE_CSV: LogEmployeeInfo(line); break;
    //         default: return false;
    //     }
    // }

    // file.close();
    // return FILE_NOT_EMPTY;

    ifstream file(path);
    if (!file.is_open()) return false;

    string line;
    if (!getline(file, line)) return FILE_EMPTY;  // Bỏ qua tiêu đề

    // Tạo danh sách future để chạy các luồng song song
    vector<future<void>> futures;

    while (getline(file, line))
    {
        // Mỗi dòng sẽ được xử lý trong một luồng riêng
        futures.emplace_back(async(launch::async, [this, line, infotype]() 
        {
            switch (infotype)
            {
                case GUESS_CSV: LogGuessInfo(line); break;
                case ROOM_CSV: LogRoomInfo(line); break;
                case SERVICE_CSV: LogServiceInfo(line); break;
                case EMPLOYEE_CSV: LogEmployeeInfo(line); break;
                default: return;
            }
        }));
    }

    // Đợi tất cả các luồng hoàn thành
    for (auto &fut : futures) 
    {
        fut.get();
    }

    file.close();
    return FILE_NOT_EMPTY;
}


/**
 * @brief Đọc dữ liệu khách thuê từ file CSV.
 * @param[in] line Chuỗi chứa dữ liệu đọc từ file.
 */
void File_Handle::LogGuessInfo(const string& line)
{
    // stringstream ss(line);
    // string token;
    // int room_number;
    // string name, phone, checkin, checkout;

    // getline(ss, token, ',');
    // room_number = stoi(token);
    // getline(ss, name, ',');
    // getline(ss, phone, ',');
    // getline(ss, checkin, ',');
    // getline(ss, checkout, ',');

    // list_guess.emplace_back(room_number, name, phone, checkin);

    // for (auto &room : list_room_available)
    // {
    //     for (auto &room_ : room.getRoomAvailable())
    //     {
    //         if (room_.first == room_number)
    //         {
    //             room.CheckInRoom(room_number);
    //             break;
    //         }
    //     }
    // }

    // for (auto &guess : list_guess)
    // {
    //     if (guess.getName() == name)
    //     {
    //         guess.setCheckOut(checkout);
    //         break;
    //     }
    // }

    stringstream ss(line);
    string token;
    int room_number;
    string name, phone, checkin, checkout;

    getline(ss, token, ',');
    room_number = stoi(token);
    getline(ss, name, ',');
    getline(ss, phone, ',');
    getline(ss, checkin, ',');
    getline(ss, checkout, ',');

    // Dùng mutex để đảm bảo dữ liệu không bị ghi đè khi có nhiều luồng
    {
        lock_guard<mutex> lock(guess_mutex);
        list_guess.emplace_back(room_number, name, phone, checkin);
    }

    // Cập nhật trạng thái phòng
    {
        lock_guard<mutex> lock(room_mutex);
        for (auto &room : list_room_available)
        {
            for (auto &room_ : room.getRoomAvailable())
            {
                if (room_.first == room_number)
                {
                    room.CheckInRoom(room_number);
                    break;
                }
            }
        }
    }
}


/**
 * @brief Đọc dữ liệu phòng từ file CSV.
 * @param[in] line Chuỗi chứa dữ liệu đọc từ file.
 */
void File_Handle::LogRoomInfo(const string& line)
{
    // stringstream ss(line);
    // string token;
    // int number, status;

    // getline(ss, token, ',');
    // number = stoi(token);
    // getline(ss, token, ',');
    // status = stoi(token);

    // room_available_dtype room;
    // room[number] = static_cast<available_roomstatus>(status);
    // list_room_available.emplace_back(room);

    // for (auto &room : list_room_default)
    // {
    //     for (auto &room_ : room)
    //     {
    //         if (room_.first == number)
    //         {
    //             room_.second = Available;
    //             break;
    //         }
    //     }
    // }

    stringstream ss(line);
    string token;
    int number, status;

    getline(ss, token, ',');
    number = stoi(token);
    getline(ss, token, ',');
    status = stoi(token);

    room_available_dtype room;
    room[number] = static_cast<available_roomstatus>(status);

    {
        lock_guard<mutex> lock(room_mutex);
        list_room_available.emplace_back(room);
    }

    // Cập nhật trạng thái phòng mặc định
    {
        lock_guard<mutex> lock(room_mutex);
        for (auto &room : list_room_default)
        {
            for (auto &room_ : room)
            {
                if (room_.first == number)
                {
                    room_.second = Available;
                    break;
                }
            }
        }
    }
}


/**
 * @brief Đọc dữ liệu dịch vụ từ file CSV.
 * @param[in] line Chuỗi chứa dữ liệu đọc từ file.
 */
void File_Handle::LogServiceInfo(const string& line)
{
    // stringstream ss(line);
    // string token;
    // int option, price;

    // getline(ss, token, ',');
    // option = stoi(token);
    // getline(ss, token, ',');
    // price = stoi(token);

    // service_option option_service = static_cast<service_option>(option);
    // list_service.emplace_back(option_service, price);

    stringstream ss(line);
    string token;
    int option, price;

    getline(ss, token, ',');
    option = stoi(token);
    getline(ss, token, ',');
    price = stoi(token);

    service_option option_service = static_cast<service_option>(option);

    {
        lock_guard<mutex> lock(service_mutex);
        list_service.emplace_back(option_service, price);
    }
}


/**
 * @brief Đọc dữ liệu dịch vụ từ file CSV.
 * @param[in] line Chuỗi chứa dữ liệu đọc từ file.
 */
void File_Handle::LogEmployeeInfo(const string& line)
{
    // stringstream ss(line);
    // string id, name, phone, position, workshift, password;

    // getline(ss, id, ',');
    // getline(ss, name, ',');
    // getline(ss, phone, ',');
    // getline(ss, position, ',');
    // getline(ss, workshift, ',');
    // getline(ss, password, ',');

    // list_employees.emplace_back(id, name, phone, position);
    // accountList.emplace_back(phone, password);

    stringstream ss(line);
    string id, name, phone, position, workshift, password;

    getline(ss, id, ',');
    getline(ss, name, ',');
    getline(ss, phone, ',');
    getline(ss, position, ',');
    getline(ss, workshift, ',');
    getline(ss, password, ',');

    {
        lock_guard<mutex> lock(employee_mutex);
        list_employees.emplace_back(id, name, phone, position);
        accountList.emplace_back(phone, password);
    }
}