# Simplified Wordle
 Bài tập lớn cho môn lập trình nâng cao
 Video Demo cách chơi: [TẠI ĐÂY](https://drive.google.com/file/d/1Zy1dSHkcFeDH7cb4ViUYGUAe4F4b3M0a/view?usp=sharing)
## Hướng dẫn cách chơi
 Với mỗi vòng chơi, nhiệm vụ của người chơi là tìm ra từ bí mật gồm 5 chữ cái, người chơi có thể đoán tối đa 6 lần. 
 ![Grid Demo](assets/ui/guess_grid.png)
 Mỗi lần người chơi nhập 1 từ, người chơi sẽ nhận được gợi ý cho lần đoán tiếp theo dựa vào màu của từng ô chữ. Cụ thể:
 - Nếu chữ cái đúng và nằm ở vị trí chính xác, ô chữ sẽ chuyển sang màu xanh lá. ![Correct letter](assets/ui/CellColor/grid_green.png)
 - Nếu chữ cái có trong từ nhưng sai vị trí, nó sẽ được tô màu vàng. ![Misplaced Letter](assets/ui/CellColor/grid_yellow.png)
 - Còn nếu chữ cái không có trong từ bí mật, ô chữ sẽ hiển thị màu xám. ![Wrong Letter](assets/ui/CellColor/grid_gray.png)
 
Trò chơi sẽ kết thúc khi người chơi đã đoán ra từ đó hoặc người chơi hết lượt đoán.

_**Lưu ý:**_ Người chơi có thể từ bỏ giữa chừng bằng cách bấm vào nút _"Give up"_ ở góc trên bên phải. ![Give up](assets/ui/giveup_button.png)
