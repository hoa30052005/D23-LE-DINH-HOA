# D23-LE-DINH-HOA


## BÁO CÁO LAB – THƯ VIỆN GPIO  


---

## 1. Giới thiệu
Trong bài thực hành này, em xây dựng một thư viện GPIO đơn giản cho vi điều khiển STM32 bằng phương pháp lập trình trực tiếp thanh ghi (Register Level). Thư viện cho phép cấu hình GPIO ở chế độ Output và điều khiển LED sáng theo dạng chạy dần.



---

## 2. Mục tiêu bài lab
- Hiểu cách cấp xung clock cho GPIO thông qua thanh ghi RCC  
- Cấu hình GPIO ở chế độ Output bằng CRL và CRH  
- Ghi dữ liệu ra GPIO bằng thanh ghi ODR  
- Xây dựng và sử dụng thư viện GPIO (.h, .c)  
- Điều khiển LED bằng lập trình thanh ghi  

---

## 3. Môi trường thực hiện
- Vi điều khiển: STM32F10x  
- Ngôn ngữ lập trình: C  
- IDE: Visual Studio Code  
- Thư viện sử dụng: CMSIS (`stm32f10x.h`)  

---

## 4. Cấu trúc chương trình
# File gpio.h
File `gpio.h` chứa khai báo nguyên mẫu các hàm được sử dụng trong thư viện GPIO.

```c
void configGPIO(GPIO_TypeDef* GPIOx);
void delay(int time);
void Blink_Led(GPIO_TypeDef* GPIOx);
```
+ configGPIO(GPIO_TypeDef* GPIOx)
Dùng để cấu hình GPIO ở chế độ Output.

+ delay(int time)
Tạo độ trễ bằng vòng lặp rỗng.

+ Blink_Led(GPIO_TypeDef* GPIOx)
Điều khiển LED sáng dần trên GPIO.

# File gpio.c
```c
void configGPIO(GPIO_TypeDef* GPIOx){
    if (GPIOx == GPIOA) RCC->APB2ENR |= 0x04;
    else if (GPIOx == GPIOB) RCC->APB2ENR |= 0x08;
    else if (GPIOx == GPIOC) RCC->APB2ENR |= 0x10;

    GPIOx->CRL = 0x11111111;
    GPIOx->CRH = 0x11111111;
}
```
+ RCC->APB2ENR: thanh ghi cấp xung clock cho ngoại vi trên bus APB2

+ Bit cấp xung:
- GPIOA: bit 2
- GPIOB: bit 3
- GPIOC: bit 4

+ Nếu GPIO không được cấp xung clock thì các thanh ghi GPIO sẽ không hoạt động.

+ CRL: cấu hình các chân từ 0 đến 7
+ CRH: cấu hình các chân từ 8 đến 15
+ Giá trị 0x1 tương ứng:

- MODE = 01 → Output tốc độ 10 MHz

- CNF = 00 → Output push-pull

→ Tất cả các chân GPIO được cấu hình là OUTPUT.



```c
void delay(int time){
    int i, j;
    for(i = 0; i < time; i++){
        for(j = 0; j < 0x2aff; j++);
    }
}
```
+ Hàm tạo trễ bằng cách sử dụng vòng lặp rỗng
+ Thời gian trễ chỉ mang tính tương đối
+ Phụ thuộc vào tần số clock của vi điều khiển
+ Hàm delay được sử dụng để quan sát trạng thái thay đổi của LED.



```c
void Blink_Led(GPIO_TypeDef* GPIOx){
    int mang[9] = {0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF};
    int i;
    for(i = 0; i < 9; i++){
        GPIOx->ODR = mang[i];
        delay(100);
    }
}
```
+ mang[] chứa các giá trị nhị phân điều khiển LED sáng dần

+ Mỗi phần tử tương ứng với trạng thái bật các bit từ thấp lên cao




# Chương trình chính main.c
```c
int main(){
    configGPIO(GPIOA);
    while(1){
        Blink_Led(GPIOA);
    }
}
```

+ Cấu hình GPIOA ở chế độ Output

+ Gọi hàm Blink_Led(GPIOA) liên tục trong vòng lặp vô hạn

+ LED chạy liên tục trong suốt quá trình hoạt động
