var tree_structure = {
    chart: {
        container: "#ASTTree",
        levelSeparation:    25,
        siblingSeparation:  70,
        subTeeSeparation:   70,
        nodeAlign: "BOTTOM",
        scrollbar: "fancy",
        padding: 35,
        node: { HTMLclass: "evolution-tree" },
        connectors: {
            type: "curve",
            style: {
                "stroke-width": 2,
                "stroke-linecap": "round",
                "stroke": "#ccc"
            }
        }
    },

    nodeStructure: {text:{name:"ASTProgram",desc:"1.1-36.4"},children:[{text:{name:"ASTProgramHead",desc:"1.1-1.15"},children:[]},{text:{name:"ASTProgramBody",desc:"2.1-36.4"},children:[{text:{name:"ASTProgramBlock",desc:"2.1-36.3"},children:[{text:{name:"ASTLabelDeclPart",desc:"2.1-2.16"},children:[{text:{name:"ASTLabelList",desc:"2.7-2.15"},children:[{text:{name:"ASTLabel",desc:"2.7-2.11"},children:[]},{text:{name:"ASTLabel",desc:"2.13-2.15"},children:[]}]}]},{text:{name:"ASTConstDeclPart",desc:"3.1-7.3"},children:[{text:{name:"ASTConstDeclList",desc:"4.5-5.19"},children:[{text:{name:"ASTConstDecl",desc:"4.5-4.11"},children:[{text:{name:"ASTConst",desc:"4.10-4.10"},children:[]}]},{text:{name:"ASTConstDecl",desc:"5.5-5.19"},children:[{text:{name:"ASTConst",desc:"5.11-5.18"},children:[]}]}]}]},{text:{name:"ASTVarDeclPart",desc:"7.1-9.9"},children:[{text:{name:"ASTVarDeclList",desc:"8.5-8.18"},children:[{text:{name:"ASTVarDecl",desc:"8.5-8.18"},children:[{text:{name:"ASTIdentifierList",desc:"8.5-8.8"},children:[{text:{name:"a"},children:[]},{text:{name:"b"},children:[]}]},{text:{name:"ASTTypeOrdinalBase",desc:"8.11-8.17"},children:[]}]}]}]},{text:{name:"ASTProcFuncDefPart",desc:"9.1-20.4"},children:[{text:{name:"ASTProcedureDeclaration",desc:"9.1-15.4"},children:[{text:{name:"ASTProcedureHead",desc:"9.1-9.30"},children:[{text:{name:"ASTFormalParamList",desc:"9.18-9.29"},children:[{text:{name:"ASTFormalParamValue",desc:"9.18-9.29"},children:[{text:{name:"ASTIdentifierList",desc:"9.18-9.21"},children:[{text:{name:"m"},children:[]},{text:{name:"n"},children:[]}]},{text:{name:"ASTTypeOrdinalBase",desc:"9.23-9.29"},children:[]}]}]}]},{text:{name:"ASTProcedureBody",desc:"9.31-15.4"},children:[{text:{name:"ASTProgramBlock",desc:"9.31-15.3"},children:[{text:{name:"ASTStatPart",desc:"10.1-15.3"},children:[{text:{name:"ASTCompoundStat",desc:"10.1-15.3"},children:[{text:{name:"ASTStatList",desc:"11.5-14.31"},children:[{text:{name:"ASTStatCondIf",desc:"11.5-14.30"},children:[{text:{name:"ASTExprBinary",desc:"11.8-11.17"},children:[{text:{name:"ASTExprIdentifier",desc:"11.8-11.10"},children:[]},{text:{name:"ASTExprIdentifier",desc:"11.12-11.17"},children:[]}]},{text:{name:"ASTStatProc",desc:"12.9-12.30"},children:[{text:{name:"ASTActualParamList",desc:"12.17-12.30"},children:[{text:{name:"ASTActualParam",desc:"12.17-12.30"},children:[{text:{name:"ASTExprConst",desc:"12.17-12.30"},children:[{text:{name:"ASTConst",desc:"12.17-12.29"},children:[]}]}]}]}]},{text:{name:"ASTStatProc",desc:"14.9-14.30"},children:[{text:{name:"ASTActualParamList",desc:"14.17-14.30"},children:[{text:{name:"ASTActualParam",desc:"14.17-14.30"},children:[{text:{name:"ASTExprConst",desc:"14.17-14.30"},children:[{text:{name:"ASTConst",desc:"14.17-14.29"},children:[]}]}]}]}]}]}]}]}]}]}]}]},{text:{name:"ASTFunctionDeclaration",desc:"17.1-20.4"},children:[{text:{name:"ASTFunctionHead",desc:"17.1-17.20"},children:[{text:{name:"ASTTypeOrdinalBase",desc:"17.14-17.20"},children:[]}]},{text:{name:"ASTFunctionBody",desc:"17.21-20.4"},children:[{text:{name:"ASTProgramBlock",desc:"17.21-20.3"},children:[{text:{name:"ASTStatPart",desc:"18.1-20.3"},children:[{text:{name:"ASTCompoundStat",desc:"18.1-20.3"},children:[{text:{name:"ASTStatList",desc:"19.5-19.15"},children:[{text:{name:"ASTStatAssign",desc:"19.5-19.15"},children:[{text:{name:"ASTExprIdentifier",desc:"19.5-19.15"},children:[]},{text:{name:"ASTExprConst",desc:"19.11-19.15"},children:[{text:{name:"ASTConst",desc:"19.11-19.14"},children:[]}]}]}]}]}]}]}]}]}]},{text:{name:"ASTStatPart",desc:"22.1-36.3"},children:[{text:{name:"ASTCompoundStat",desc:"22.1-36.3"},children:[{text:{name:"ASTStatList",desc:"24.5-34.20"},children:[{text:{name:"ASTStatAssign",desc:"24.5-24.11"},children:[{text:{name:"ASTExprIdentifier",desc:"24.5-24.11"},children:[]},{text:{name:"ASTExprConst",desc:"24.10-24.11"},children:[{text:{name:"ASTConst",desc:"24.10-24.10"},children:[]}]}]},{text:{name:"ASTStatAssign",desc:"25.5-25.15"},children:[{text:{name:"ASTExprIdentifier",desc:"25.5-25.15"},children:[]},{text:{name:"ASTExprBinary",desc:"25.10-25.15"},children:[{text:{name:"ASTExprIdentifier",desc:"25.10-25.12"},children:[]},{text:{name:"ASTExprConst",desc:"25.14-25.14"},children:[{text:{name:"ASTConst",desc:"25.14-25.14"},children:[]}]}]}]},{text:{name:"ASTStatAssign",desc:"26.5-26.15"},children:[{text:{name:"ASTExprIdentifier",desc:"26.5-26.15"},children:[]},{text:{name:"ASTExprBinary",desc:"26.10-26.15"},children:[{text:{name:"ASTExprIdentifier",desc:"26.10-26.10"},children:[]},{text:{name:"ASTExprConst",desc:"26.14-26.14"},children:[{text:{name:"ASTConst",desc:"26.14-26.14"},children:[]}]}]}]},{text:{name:"ASTStatAssign",desc:"27.5-27.15"},children:[{text:{name:"ASTExprIdentifier",desc:"27.5-27.15"},children:[]},{text:{name:"ASTExprBinary",desc:"27.10-27.15"},children:[{text:{name:"ASTExprIdentifier",desc:"27.10-27.10"},children:[]},{text:{name:"ASTExprConst",desc:"27.14-27.14"},children:[{text:{name:"ASTConst",desc:"27.14-27.14"},children:[]}]}]}]},{text:{name:"ASTStatAssign",desc:"29.5-29.22"},children:[{text:{name:"ASTExprIdentifier",desc:"29.12-29.22"},children:[]},{text:{name:"ASTExprBinary",desc:"29.17-29.22"},children:[{text:{name:"ASTExprIdentifier",desc:"29.17-29.19"},children:[]},{text:{name:"ASTExprConst",desc:"29.21-29.21"},children:[{text:{name:"ASTConst",desc:"29.21-29.21"},children:[]}]}]}]},{text:{name:"ASTStatCondIf",desc:"31.5-34.19"},children:[{text:{name:"ASTExprBinary",desc:"31.8-31.19"},children:[{text:{name:"ASTExprIdentifier",desc:"31.9-31.11"},children:[]},{text:{name:"ASTExprIdentifier",desc:"31.13-31.14"},children:[]}]},{text:{name:"ASTStatGoto",desc:"32.8-32.17"},children:[]},{text:{name:"ASTStatProc",desc:"34.9-34.19"},children:[{text:{name:"ASTActualParamList",desc:"34.15-34.19"},children:[{text:{name:"ASTActualParam",desc:"34.15-34.16"},children:[{text:{name:"ASTExprIdentifier",desc:"34.15-34.16"},children:[]}]},{text:{name:"ASTActualParam",desc:"34.18-34.19"},children:[{text:{name:"ASTExprIdentifier",desc:"34.18-34.19"},children:[]}]}]}]}]}]}]}]}]}]}]}
};