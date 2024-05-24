# GameSDL
 


# Shooting
This is the game made project of INT2215 class, using C++ with SDL2 library.

#Guide
In this game, The player must pass through the forest to reach the final destination. In the process, the player will encounter monsters and the player's task must be to overcome the monsters. Player use guns to fend off these monsters and protect themselves.

The players will die if they are killed by the monster or they do not keep a certain distance with the Boss.

With each monster is killed by players, they will get 1 point, if the monsters are touch the Boss before being killed, Players will be deducted 1 point

Remember that if the players do not keep their distance from the Boss, they will die immediately even if they have remaining health.

#About this game

It is a basic game using C++ with SDL2 library.
Game em thiết kế là 1 game vượt ải khá quen thuộc và basic. Game có các menu chính như chỉ dẫn, thoát, dừng game, chọn nhân vật.... Phần lớn đồ họa được lấy từ các nguồn mở trên internet và được chọn lọc sao cho phù hợp với bối cảnh game.

Nhân vật sẽ có 5 lượt máu, sau mỗi lần bị quái chém sẽ mất 1 máu và không thể tự phục hồi. Nhân vật sử dụng súng để giết quái (việc giết quái diễn ra khá dễ do quái được bố trí nhiều theo map cụ thể)

Em có sử dụng 1 con Boss lớn chạy xuyên suốt game với mục đích giục người chơi không thể quay đầu, phải di chuyển và cố gắng bắn hết quái trên đường đi qua. 

Map được sinh ngẫu nhiên và vô hạn ( tức là game chỉ kết thúc khi người chơi chết hoặc muốn thoát game). Có tất cả 6 map được thiết kế, trong đó map0 khởi đầu luôn luôn được xuất hiện đầu tiên, sau đó sẽ vẽ các map khác lần lượt 1 cách random, vị trí của các quái cũng được đánh dấu sẵn trên các map tương ứng.

(*) Nhân vật sẽ chết nếu hết máu hoặc chạm vào Boss. Tương tự với quái, chỉ khác là nếu quái bị nhân vật bỏ qua và chạm vào Boss, nhân vật sẽ bị trừ 1 điểm (sẽ bị trừ về 0)


#Some notes for my project:

Một vài lỗi về xử lý bộ nhớ em mới phát hiện sau khi quá hạn nộp bài, rất mong thầy thông cảm vì sự thiếu sót này. Em sẽ cố gắng sửa nó sau đó.

#Setup guide
Install CodeBlocks, Visual Studio 2019, Visual Studio Code, XCode,... then download this project and run. Remember that we use SDL Lib, you can follow tutorials on

#Screen Shot
//…//

#Video Demo
//…//

#Credit
assets/sounds/img are from internet (cre: itch.io)
Free font from Google Fonts
Các nguồn tham khảo: Youtube, Lazyfoo và các bạn học giỏi trong lớp:)))))
