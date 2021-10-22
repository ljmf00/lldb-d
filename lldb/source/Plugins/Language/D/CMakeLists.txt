add_lldb_library(lldbPluginDLanguage PLUGIN
  DLanguage.cpp
  DTypeUtils.cpp
  DFormatterFunctions.cpp

  LINK_LIBS
    lldbCore
    lldbDataFormatters
    lldbSymbol
    lldbTarget
  LINK_COMPONENTS
    Support
)
