{
'target_defaults': {
	'default_configuration': 'Debug',
	'configurations': {
		'Debug': {
			'defines': [ 'DEBUG', '_DEBUG' ],
			'msvs_settings': {
				'VCCLCompilerTool': {
					'RuntimeLibrary': 1, 
					'BasicRuntimeChecks': 0,
					'Optimization': 0,
				},
				'VCLinkerTool': {
					'LinkIncremental': 1,
					'GenerateDebugInformation': 'true',
				},        
			},
		},
		'Release': {
			'defines': [ 'NDEBUG' ],
			'msvs_settings': {
				'VCCLCompilerTool': {
					'RuntimeLibrary': 0,
					'Optimization': 3,
					'FavorSizeOrSpeed': 1,
					'InlineFunctionExpansion': 2,
					'WholeProgramOptimization': 'true',
					'OmitFramePointers': 'true',
					'EnableFunctionLevelLinking': 'true',
					'EnableIntrinsicFunctions': 'true'            
				},
				'VCLinkerTool': {
					'LinkTimeCodeGeneration': 1,
					'OptimizeReferences': 2,
					'EnableCOMDATFolding': 2,
					'LinkIncremental': 1,          
				},
			},
		},
		'ReleaseDbgInfo': {
			'defines': [ 'NDEBUG' ],
			'msvs_settings': {
				'VCCLCompilerTool': {
					'RuntimeLibrary': 0,
					'Optimization': 3,
					'FavorSizeOrSpeed': 1,
					'InlineFunctionExpansion': 2,
					'WholeProgramOptimization': 'true',
					'OmitFramePointers': 'true',
					'EnableFunctionLevelLinking': 'true',
					'EnableIntrinsicFunctions': 'true'            
				},
				'VCLinkerTool': {
					'LinkTimeCodeGeneration': 1,
					'OptimizeReferences': 2,
					'EnableCOMDATFolding': 2,
					'LinkIncremental': 1,     
					'GenerateDebugInformation': 'true',
				},
			},
		},
	},
},
}
