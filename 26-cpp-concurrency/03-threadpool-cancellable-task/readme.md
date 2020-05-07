## ThreadPool

### Class with atomic or mutex

因为 atomic, mutex 无法 copy, move。所以类中如果包含了这样的属性，对应的 copy, move 构造函数也需要有相应的实现。

### How to cancel a task

1. [HOW TO STOP A STD::ASYNC TASK](https://studiofreya.com/2015/07/05/how-to-stop-a-std-async-task/)
