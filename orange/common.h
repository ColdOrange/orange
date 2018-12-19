//
// Created by wenjuxu on 2018/12/19.
//

#ifndef ORANGE_COMMON_H
#define ORANGE_COMMON_H

#define STRING_CONCAT_IMPL(A, B) A##B
#define STRING_CONCAT(A, B) STRING_CONCAT_IMPL(A, B)

#define UNIQUE_NAME(X) STRING_CONCAT(X, __LINE__)

#endif // ORANGE_COMMON_H
