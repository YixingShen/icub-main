# Copyright: (C) 2015 iCub Facility
# Authors: Marco Randazzo <marco.randazzo@iit.it>
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

yarp_prepare_plugin(bcbBattery CATEGORY device TYPE BcbBattery INCLUDE bcbBattery.h EXTRA_CONFIG WRAPPER=BatteryWrapper)

if(NOT SKIP_bcbBattery)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                       ${YARP_INCLUDE_DIRS})

yarp_add_plugin(bcbBattery bcbBattery.h bcbBattery.cpp)
target_link_libraries(bcbBattery ${YARP_LIBRARIES})

icub_export_plugin(bcbBattery)

yarp_install(FILES bcbBattery.ini  DESTINATION ${ICUB_PLUGIN_MANIFESTS_INSTALL_DIR})

endif (NOT SKIP_bcbBattery)
