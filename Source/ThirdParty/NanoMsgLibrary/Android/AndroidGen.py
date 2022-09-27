import argparse
import pathlib
from string import Template


class MyTemplate(Template):
    delimiter = '@'


template = MyTemplate(
    """
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := @local_src_files

LOCAL_CFLAGS := \\
    -DNN_HAVE_EPOLL \\
    -DNN_USE_EPOLL \\
    -DNN_HAVE_KQUEUE \\
    -DNN_USE_KQUEUE \\
    -DNN_HAVE_POLL \\
    -DNN_USE_POLL \\
    -DNN_HAVE_PIPE \\
    -DNN_USE_PIPE \\
    -DNN_HAVE_SOCKETPAIR \\
    -DNN_USE_SOCKETPAIR \\
    -DNN_HAVE_WINSOCK \\
    -DNN_USE_WINSOCK \\
    -DNN_HAVE_MSG_CONTROL

LOCAL_MODULE := libnanomsg
LOCAL_MODULE_TAGS := optional

LOCAL_COPY_HEADERS := bus.h inproc.h ipc.h nn.h pair.h pipeline.h pubsub.h reqrep.h survey.h tcp.h ws.h
LOCAL_COPY_HEADERS_TO := nanomsg
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src

TARGET_PLATFORM := @target_platform
TARGET_ARCH_ABI := @target_arch_abi

include $(BUILD_SHARED_LIBRARY)
"""
)


def parse_args():
    parser = argparse.ArgumentParser(
        prog='generator Android.mk file for nanomsg project.', add_help=True)
    parser.add_argument(
        '-r',
        '--root',
        type=str,
        required=True,
        help='source dir')
    parser.add_argument(
        '-a',
        '--target_arch_abi',
        type=str,
        default='all',
        choices=['armeabi', 'armeabi-v7a', 'x86', 'x86_64 arm64-v8a'],
        help='target arch abi')
    parser.add_argument(
        '-p',
        '--target_platform',
        type=str,
        default='android-21',
        help='target platform')
    parser_args = parser.parse_args()
    return parser_args


def main():
    args = parse_args()

    root = pathlib.Path(args.root)
    src_files = root.joinpath('src').rglob("*.c")
    src_files = [str(s.relative_to(root).as_posix()) for s in src_files]

    temp = template.substitute(
        local_src_files=' \\ \n \t'.join(src_files),
        target_platform=args.target_platform,
        target_arch_abi=args.target_arch_abi,
    )

    print("Android.mk:")
    print(temp)
    print("You can copy config to Android.mk, and run with: 'ndk-build.cmd NDK_PROJECT_PATH=/Source/PathTo/nanomsg'")


if __name__ == "__main__":
    main()
