// Copyright (c) 2024 YukiHino. All rights reserved.

#pragma once

#include <memory>

template <class T>
using u_ptr = std::unique_ptr<T>;

template <class T>
using s_ptr = std::shared_ptr<T>;

template <class T>
using w_ptr = std::weak_ptr<T>;
