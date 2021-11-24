add_lldb_library(lldbPluginTypeSystemD PLUGIN
  TypeSystemD.cpp

  LINK_LIBS
    lldbCore
    lldbSymbol
    lldbTarget
    lldbUtility
    lldbPluginExpressionParserClang
    lldbPluginSymbolFileDWARF
    lldbPluginSymbolFilePDB
    lldbPluginObjCRuntime
  LINK_COMPONENTS
    Support
)
