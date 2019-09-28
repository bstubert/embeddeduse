# Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

cmake_minimum_required(VERSION 3.5)

add_subdirectory(test_j1939_frames)
add_subdirectory(test_mock_can_frames)
add_subdirectory(test_connect_to_mock_can_bus)
add_subdirectory(test_read_write_on_mock_can_bus)
add_subdirectory(test_receive_frames_from_two_ecus)
add_subdirectory(test_write_buffer_overflow)

