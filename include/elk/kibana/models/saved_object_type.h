//
// Created by tnwei on 1/16/2022.
//

#ifndef ELK_CPP_CLIENT_SRC_ELK_CLIENT_KIBANA_MODELS_SAVED_OBJECT_TYPE_H_
#define ELK_CPP_CLIENT_SRC_ELK_CLIENT_KIBANA_MODELS_SAVED_OBJECT_TYPE_H_

#include "elk/external/magic_enum.hpp"

namespace elk {
  enum class SavedObjectType {
    VISUALIZATION,
    DASHBOARD,
    SEARCH,
    INDEX_PATTERN,
    CONFIG
  };
}
#endif //ELK_CPP_CLIENT_SRC_ELK_CLIENT_KIBANA_MODELS_SAVED_OBJECT_TYPE_H_
