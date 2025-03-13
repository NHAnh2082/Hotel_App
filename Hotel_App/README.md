# Quản Lý Khách Sạn

## 📌 Giới Thiệu Dự Án
Hệ thống **Quản lý Khách Sạn** được phát triển bằng C++ nhằm hỗ trợ quản lý nhân viên, phòng, dịch vụ và đặt phòng khách sạn. Chương trình sử dụng giao diện dòng lệnh và lưu trữ dữ liệu bằng tệp CSV.

## 🌟 Chức Năng Nổi Bật
- **Quản lý nhân viên**: Thêm, sửa, xóa nhân viên, set ca làm việc.
- **Quản lý phòng**: Thêm, chỉnh sửa, xóa và theo dõi tình trạng phòng.
- **Quản lý dịch vụ**: Quản lý danh sách dịch vụ kèm giá cả.
- **Quản lý khách thuê**: Đặt phòng, hủy phòng, lưu thông tin khách thuê.
- **Lưu trữ và đọc dữ liệu từ file CSV**.

## 📚 Kiến Thức Sử Dụng
- **Lập trình hướng đối tượng (OOP)**: Sử dụng class cho từng thành phần như `Employee`, `Room`, `Service`.
- **Đọc/Ghi file trong C++**: Sử dụng `fstream` để thao tác với file CSV.
- **Đa luồng (Multithreading)**: Áp dụng để tăng hiệu suất khi thao tác file.
- **Lambda functions**: Tối ưu code xử lý dữ liệu.
- **STL (Standard Template Library)**: Dùng `vector`, `map` để quản lý danh sách nhân viên, phòng, dịch vụ.

## 📂 Cấu Trúc Thư Mục
```cpp
HOTEL_APP/
│── bin/                     # Chứa file thực thi sau khi build
│── database/                # Chứa file dữ liệu CSV
│   ├── employee.csv         # Danh sách nhân viên
│   ├── guess.csv            # Danh sách khách thuê
│   ├── room.csv             # Danh sách phòng
│   ├── service.csv          # Danh sách dịch vụ
│── Inc/                     # Chứa các file header
│   ├── Account.hpp
│   ├── Employee_Manager.hpp
│   ├── Employee.hpp
│   ├── File_Handling.hpp
│   ├── Manager.hpp
│   ├── Menu.hpp
│   ├── Room_Manager.hpp
│   ├── Service_Manager.hpp
│   ├── UI.hpp
│── Src/                     # Chứa các file source
│   ├── Account.cpp
│   ├── Employee_Manager.cpp
│   ├── File_Handling.cpp
│   ├── Manager.cpp
│   ├── Room_Manager.cpp
│   ├── Service_Manager.cpp
│   ├── UI.cpp
│── makefile                 # File cấu hình build dự án
```

## 📜 Mô Tả Chi Tiết Các File
### **1. `Account.hpp` & `Account.cpp`**
- Quản lý tài khoản nhân viên và quản lý.
- Hỗ trợ đăng nhập, đăng ký, kiểm tra tài khoản.

### **2. `Employee_Manager.hpp` & `Employee_Manager.cpp`**
- Quản lý danh sách nhân viên.
- Hỗ trợ thêm, sửa, xóa nhân viên.
- Đặt ca làm cho nhân viên.

### **3. `Room_Manager.hpp` & `Room_Manager.cpp`**
- Quản lý danh sách phòng.
- Thêm, chỉnh sửa, xóa phòng, kiểm tra trạng thái phòng.

### **4. `Service_Manager.hpp` & `Service_Manager.cpp`**
- Quản lý danh sách dịch vụ của khách sạn.
- Thêm, sửa, xóa dịch vụ.

### **5. `File_Handling.hpp` & `File_Handling.cpp`**
- Đọc/ghi dữ liệu từ file CSV.
- Áp dụng đa luồng để tối ưu tốc độ xử lý file.

### **6. `UI.hpp` & `UI.cpp`**
- Quản lý giao diện nhập/xuất dữ liệu từ người dùng.

### **7. `Manager.hpp` & `Manager.cpp`**
- Quản lý tổng hợp toàn bộ hệ thống.
- Hiển thị menu điều khiển chính.
- Gọi các chức năng quản lý nhân viên, phòng, dịch vụ.

### **8. `Menu.hpp` & `Menu.cpp`**
- Quản lý menu giao diện điều khiển.
- Sử dụng `vector<MenuItem>` để tạo menu linh hoạt.

### **9. `main.cpp`**
- Chương trình chính, xử lý vòng lặp đăng nhập và gọi `Manager`.

## 🚀 Hướng Dẫn Cài Đặt & Sử Dụng
### **1. Cài Đặt Công Cụ**
- C++ Compiler (`g++` hoặc `MSVC`)
- `make` (nếu sử dụng Makefile)

### **2. Biên Dịch Dự Án**
```sh
make
```
Nếu không dùng `makefile`, có thể biên dịch thủ công:
```sh
g++ -o hotel_app Src/*.cpp -IInc
```

### **3. Chạy Chương Trình**
```sh
./hotel_app
```

### **4. Sử Dụng**
1. Đăng nhập bằng tài khoản quản lý (`admin` mặc định).
2. Chọn chức năng từ menu chính để quản lý nhân viên, phòng, dịch vụ.
3. Khi hoàn thành, chọn "Lưu trữ dữ liệu" để lưu vào file CSV.

📌 **Lưu ý:** Nếu không lưu, dữ liệu có thể bị mất khi thoát chương trình.

## 📢 Đóng Góp
- Nếu bạn muốn đóng góp, vui lòng tạo **pull request** hoặc mở **issue**.

## 📜 Giấy Phép
Dự án này được phát hành theo **MIT License**. Bạn có thể sử dụng tự do với điều kiện giữ lại phần bản quyền của tác giả.

