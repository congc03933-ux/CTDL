# Quản lý danh sách thí sinh

Dự án môn Cấu trúc dữ liệu và Giải thuật, thực hiện bằng C++11.

## Mục tiêu

Quản lý thông tin thí sinh gồm họ tên, giới tính, mã dự thi,
ngày sinh và quê quán.

Các chức năng cần hoàn thành:
- Thêm thí sinh.
- Tra cứu thông tin.
- Hiển thị danh sách theo tên tăng dần.
- Chia thí sinh vào phòng thi để giảm trùng chữ cái đầu tên.
- Đọc và lưu dữ liệu TXT.

## Cấu trúc dữ liệu và giải thuật

- Bảng tra gồm 29 nhóm chữ cái tiếng Việt.
- Mỗi nhóm chứa một danh sách liên kết đơn.
- Tìm kiếm tuyến tính để kiểm tra mã dự thi trùng.
- Dự kiến dùng Merge Sort để sắp xếp danh sách.
- Dự kiến chia phòng luân phiên theo từng nhóm chữ cái.

## Phần đã thực hiện

Thành viên 1 đã cài đặt:
- Khởi tạo bảng và danh sách liên kết.
- Tạo node và thêm cuối danh sách.
- Lấy tên gọi và xác định nhóm chữ cái.
- Thêm thí sinh, kiểm tra mã dự thi trùng.
- Kiểm tra ngày sinh và các trường bắt buộc bị bỏ trống.
- Đếm thí sinh và giải phóng bộ nhớ.

main.cpp hiện dùng để kiểm thử phần thêm thí sinh,
chưa phải menu hoàn chỉnh.

## Phân công

| Thành viên | File | Công việc |
|---|---|---|
| 1 | QuanLy.cpp | Cấu trúc nền, thêm thí sinh, kiểm tra dữ liệu |
| 2 | TraCuu.cpp | Tìm theo mã, tên và chữ cái đầu |
| 3 | SapXep.cpp | Sắp xếp và hiển thị tên tăng dần |
| 4 | ChiaPhong.cpp | Phân phòng và đánh giá kết quả |
| 5 | File.cpp | Đọc, lưu hồ sơ và xuất danh sách phòng |
| 6 | main.cpp | Menu, tích hợp và kiểm thử toàn chương trình |

QuanLy.h chứa các cấu trúc và khai báo hàm dùng chung.
Mọi thay đổi trong file này cần được thống nhất với nhóm.

## Cách chạy trên Dev-C++

1. Tải hoặc clone repository về máy.
2. Mở Project1.dev.
3. Bật chuẩn C++11.
4. Biên dịch lại toàn bộ project bằng Rebuild All.
5. Chạy chương trình.

Phải biên dịch cả project, không chỉ biên dịch main.cpp.

## Quy ước dữ liệu

- Mã dự thi là chuỗi và phải duy nhất.
- Tên gọi được lấy từ cuối họ tên.
- Ngày sinh có dạng dd/mm/yyyy, ví dụ 29/06/2007.
- Dữ liệu tiếng Việt sử dụng UTF-8.
- Thông báo trong code hiện viết không dấu để phù hợp Dev-C++ 5.11.
- Hỗ trợ tên tiếng Việt dựng sẵn UTF-8; chưa chuẩn hóa dấu tách rời.

## Kiểm thử trước khi ghép code

- Thêm hồ sơ hợp lệ.
- Thêm lại cùng mã phải bị từ chối.
- Cùng tên nhưng khác mã vẫn được thêm.
- Từ chối ngày không hợp lệ và trường bắt buộc bỏ trống.
- Kiểm tra đúng nhóm của An, Ấn và Đạt.
- Kiểm tra số lượng và giải phóng bộ nhớ.

## Làm việc nhóm

- Mỗi người phụ trách file được phân công.
- Chỉ main.cpp chứa hàm main.
- Không include file cpp vào file khác.
- Không tự đổi cấu trúc hoặc tên hàm dùng chung.
- Kiểm thử phần mình trước khi gửi thay đổi.
- Không đưa file exe, file o hoặc dữ liệu cá nhân thật lên GitHub.