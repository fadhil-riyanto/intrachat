#include <stdint.h>

// 0x00001000
struct Example
{
    uint16_t data_1; // starting 0x00001001
    uint32_t data_2; // 0x00001002 to 0x00001005
    uint8_t data_3;  // starting 0x00001006
};


// #include <iostream>
// #include <cstring>

// template<typename T> void memcpy(T* dst, T* src)
// {
//     memcpy(dst,src,sizeof(T));
// }

// int main()
// {
//   struct {
//       char c;
//       int d;
//   }__attribute__((packed)) v;
//   v.d=10;
//   int e;
//   memcpy(&e,&v.d);
//   std::cout<<e;
// }

// /////////////

// #include <iostream>
// #include <cstring>

// template<typename T> void memcpy(T* dst, void* src)
// {
//     memcpy(dst,src,sizeof(T));
// }

// int main()
// {
//   struct {
//       char c;
//       int d;
//   }__attribute__((packed)) v;
//   v.d=10;
//   int e;
//   memcpy(&e,&v.d);
//   std::cout<<e;
// }
