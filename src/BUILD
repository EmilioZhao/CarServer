#proto_library(
#        name = "light_proto",
#        )
#cc_proto_library(
#        name = "light_cc_proto",
#        deps = [":light_proto"],
#        )
#cc_library (
#        name = "lib",
#        deps = [":light_cc_proto"],
#        )
cc_library (
        name = "light_proto",
        srcs = ["light.pb.cc"],
        hdrs = ["light.pb.h"],
        )
cc_binary (
       name = "perception_module",
       srcs = ["perception_module.cc"],
       deps = [":light_proto"],
        )
