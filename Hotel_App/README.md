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

## 🔧 Hướng Dẫn Cài Đặt & Sử Dụng
### 🖥️ **Cài Đặt Công Cụ**

✅ **GNU Make** (Công cụ tự động hóa quá trình biên dịch)

✅ **Trình biên dịch C++** (G++, Clang hoặc MSVC, hỗ trợ C++11 trở lên)

### 🚀 **Các Lệnh Sử Dụng Makefile**

1. 📥 **Biên dịch chương trình**

Để biên dịch toàn bộ chương trình, sử dụng lệnh sau:

```bash
make
```

Lệnh này sẽ:

- Tạo thư mục Build/ nếu chưa tồn tại.

- Biên dịch toàn bộ mã nguồn trong thư mục Source/.

- Tạo file thực thi tại Build/main.

2. 🏃 Chạy chương trình

Sau khi biên dịch thành công, chạy chương trình bằng cách:

```bash
make run
```

3. 🧹 Xóa các tệp biên dịch cũ (Clean Build)

Để xóa toàn bộ các tệp tạm trong thư mục **Build/** và biên dịch lại từ đầu:

```bash
make clean
```

4. **Sử Dụng**

B1. Đăng nhập bằng tài khoản quản lý (`admin` mặc định).
B2. Chọn chức năng từ menu chính để quản lý nhân viên, phòng, dịch vụ.
B3. Khi hoàn thành, chọn "Lưu trữ dữ liệu" để lưu vào file CSV.

📌 **Lưu ý:** Nếu không lưu, dữ liệu có thể bị mất khi thoát chương trình.

## 📢 Đề xuất cải tiến

Mặc dù dự án đã hoàn thành nhưng vẫn chưa thực sự tối ưu. Sau đây là đề xuất để có thể cải tiến chương trình:

1. **Sử dụng Smart Pointer**

- **Lợi ích**: Tránh rò rỉ bộ nhớ, tự động giải phóng tài nguyên.
- **Ứng dụng**: Thay thế các con trỏ thô trong Employee, Room, Guess bằng ``` std::unique_ptr ``` hoặc ``` std::shared_ptr ```.

2. **Áp dụng SOLID**

- **Single Responsibility Principle**: Tách File_Handling thành nhiều class nhỏ để dễ bảo trì.
- **Open/Closed Principle**: Cho phép mở rộng menu mà không cần thay đổi code cũ.
- **Dependency Inversion**: Tạo interface IStorage để xử lý lưu trữ file linh hoạt hơn.

3. **Design Patterns**

- **Singleton** (Quản lý tài khoản, database)

  + **Áp dụng**: AccountManager hoặc DatabaseManager để đảm bảo chỉ có một instance trong hệ thống.

- Factory Pattern (Tạo đối tượng linh hoạt)

  + **Áp dụng**: EmployeeFactory, ServiceFactory để tạo nhân viên hoặc dịch vụ dựa trên yêu cầu.

- Observer Pattern (Cập nhật UI khi có thay đổi dữ liệu)

  + **Áp dụng**: Khi có thay đổi trong danh sách nhân viên, phòng, hoặc dịch vụ, UI sẽ tự động cập nhật.

- MVP (Model-View-Presenter)

  + **Áp dụng**: Tách phần xử lý logic và giao diện UI, giúp dễ bảo trì và mở rộng. 

## 📜 Giấy Phép
Dự án này được phát hành theo **MIT License**. Bạn có thể sử dụng tự do với điều kiện giữ lại phần bản quyền của tác giả.

