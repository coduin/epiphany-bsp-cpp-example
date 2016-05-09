/*
File: e_e_hello.c

This file is part of the Epiphany BSP library.

Copyright (C) 2014 Buurlage Wits
Support e-mail: <info@buurlagewits.nl>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License (LGPL)
as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
and the GNU Lesser General Public License along with this program,
see the files COPYING and COPYING.LESSER. If not, see
<http://www.gnu.org/licenses/>.
*/

extern "C" {
#include <e_bsp.h>
}
#include <vector>
#include <functional>

template <typename T>
class MyClass {
  public:
    MyClass(){};
    ~MyClass(){};

    void foo(const T& a) {
        return;
    }

    virtual void bar(std::function<void(T)> f) const = 0;
};

template <typename T>
class MySubClass : public MyClass<T> {
  public:
      MySubClass() {};
      ~MySubClass() {};

      void foo(const T& a) {
          value = a;
      }

      void bar(std::function<void(T)> f) const {
          if (f)
              f(value);
          else
              ebsp_message("nullptr passed to MySubClass::bar");
      }

      T value;
};

void func(int a) {
    ebsp_message("func a = %d", a);
}

int main()
{
    bsp_begin();
    int s = bsp_pid();

    std::vector<int> vec = {5, 7, 12};

    MySubClass<int> b;
    b.foo(17);

    for (auto i : vec) {
        if (s < 4)
            b.bar(nullptr);
        else if (s < 8)
            b.bar(func);
        else
            b.bar([&i](int x) {
                    ebsp_message("lambda i = %d, x = %d", i, x);
                });
    }

    bsp_end();
    return 0;
}
