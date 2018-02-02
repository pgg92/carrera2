INSERT ALL
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1, 'am', '{1} {2} does not exist.')
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (2, 'am', '{1} {2} already exists' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (3, 'am', '{1} failed due to {2}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (4, 'am', 'Invalid input: {1}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (5, 'am', 'The input source to this node contains no data.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (6, 'am', 'The node generates empty output result.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (7, 'am', 'Invalid cost benefit matrix: {1}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (8, 'am', 'Target {1} contains only one distinct value.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (9, 'am', 'Target {1} exceeds maximum distinct values. Maximum number of distinct values allowed is {2}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (10, 'am', 'Target {1} contains unique values.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (11, 'am', 'Target {1} contains NULL value(s).' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (12, 'am', 'Target {1} contains space value(s).' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (13, 'am', 'Target {1} contains all NULL values.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (14, 'am', 'Target {1} with datatype {2} may not be compatible with the {3}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (15, 'am', 'Target {1} contains value {2} that is incompatible with existing model(s).' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (16, 'am', 'Target {1} with incompatible datatype {2} (only VARCHAR2, CHAR, NUMBER, or FLOAT is allowed).' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (17, 'am', 'Case Id {1} does not contain unique values.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (18, 'am', '{1} {2} is missing.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (19, 'am', '{1} {2} has too many distinct values. Maximum number of distinct values allowed is {3}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (20, 'am', 'GLM only accepts a binary target specification (two values). The selected target {1} contains more than two values.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (21, 'am', 'Invalid apply attribute: {1}.  The attribute has datatype {2}, but the attribute used to build the model {3} has datatype {4}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (22, 'am', 'Workflow run is cancelled by user.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (23, 'am', 'Workflow is not running.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (24, 'am', 'No theme is generated for column {1}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (25, 'am', 'No Predictor found in the training data for model build.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (26, 'am', 'Input column {1} with incompatible datatype {2} (only VARCHAR2, CHAR, NUMBER, or FLOAT is allowed).' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (27, 'am', 'Input column {1} with incompatible datatype {2} (only VARCHAR2, CHAR, NUMBER, FLOAT, DM_NESTED_NUMERICALS, or DM_NESTED_CATEGORICALS is allowed).' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (28, 'am', '{1} {2} used by the Text Transformation is missing.  Execute the corresponding Build Text node to recreate the {3}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (29, 'am', 'Failed to delete the project due to contained workflow(s) is used in different session or is running.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (30, 'am', 'Table or View is not granted directly to current user. This will result in failures when Data Miner attempts to create a view. Table/View: {1}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (31, 'am', 'Workflow failed due to unexpected failure in the following nodes, please review if there were any core dumps generated: {1}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (32, 'am', 'Target {1} with incompatible datatype {2} (only VARCHAR2, CHAR, NUMBER, FLOAT, BINARY_DOUBLE, or BINARY_FLOAT is allowed).' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (33, 'am', 'Target {1} with incompatible numerical datatype {2} (only NUMBER, or FLOAT is allowed).' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (34, 'am', 'Target {1} with incompatible numerical datatype {2} (only NUMBER, FLOAT, BINARY_DOUBLE, or BINARY_FLOAT is allowed).' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (35, 'am', 'Import workflow version {1} is incompatible with the repository.  Import aborted.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (36, 'am', 'The Attribute Importance target column {1} distinct count {2} >= {3} cutoff value. This may stress system resources and result in a query failure depending on the systems capabilities. Consider binning the column prior to running this node or change the sample setting to random.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (37, 'am', 'The Attribute Importance target column {1} distinct count {2} >= {3} cutoff value. This may result in a longer running process.  Consider binning the column prior to running this node.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (38, 'am', '{1} {2} has distinct count > {3} cutoff value. This may lead to potential poorer Association Rules model. Consider binning the column prior to running this node.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (39, 'am', 'The input source data structure to this node have been changed.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (40, 'am', 'Failed to generate JSON data structure information: {1}' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (41, 'am', 'JSON Parser is not installed.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (42, 'am', 'JSON column {1} contains data that has structural change.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (43, 'am', 'Explore node statistics table no longer exists. Rerun node to recreate table.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (44, 'am', 'Column {1} is missing from generated statistics table.')
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (45, 'am', 'Workflow import failed due to following object name conflicts with existing workflows: {1}.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (46, 'am', 'Process is enqueued because maximum number ({1}) of concurrent {2} processes is reached.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (47, 'am', 'Process starts running.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (48, 'am', 'Process lock wait timeout ({1} secs) exceeded.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1000, 'am', 'Data Source' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1001, 'am', 'Workflow' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1002, 'am', 'Quantile binning' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1003, 'am', 'One of the columns does not have enough data' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1004, 'am', 'Binning Validation' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1005, 'am', 'Data does not have enough distinct values' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1006, 'am', 'Table' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1007, 'am', 'Validation' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1008, 'am', 'missing table:' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1009, 'am', 'Attribute' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1010, 'am', 'missing attribute(s)' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1011, 'am', 'Aggregation' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1012, 'am', 'Update Table' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1013, 'am', 'Input is incorrect' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1014, 'am', 'View' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1015, 'am', 'Create Table or View' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1016, 'am', 'Explore Data' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1017, 'am', 'Build' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1018, 'am', 'Test' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1019, 'am', 'Input data is empty' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1020, 'am', 'Target' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1021, 'am', 'attribute' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1022, 'am', 'incompatible input/target/case id attributes' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1023, 'am', 'Model' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1024, 'am', 'missing model' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1025, 'am', 'GLM only accepts a binary target specification (two values). The selected target contains more than two values.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1026, 'am', 'invalid item value attribute' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1027, 'am', 'missing model(s)' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1028, 'am', 'Apply' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1029, 'am', 'No validation performed' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1030, 'am', 'Model Details' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1031, 'am', 'Test Details' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1032, 'am', 'Filter Details' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1033, 'am', 'Features Table' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1034, 'am', 'Policy' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1035, 'am', 'Lexer' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1036, 'am', 'Stoplist' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1037, 'am', 'incompatible case id attribute' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1038, 'am', 'Table Column' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1039, 'am', 'incompatible column attribute' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1040, 'am', 'Join' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1041, 'am', 'Text' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1042, 'am', 'Split' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1043, 'am', 'Column' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1044, 'am', 'Sample' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1045, 'am', 'Column Filter' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1046, 'am', 'Row Filter' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1047, 'am', 'Transformation' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1048, 'am', 'Workflow Save' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1049, 'am', 'workflow was not locked by the user' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1050, 'am', 'Workflow Run' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1051, 'am', 'workflow is already running' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1052, 'am', 'workflow is already used by another session' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1053, 'am', 'Workflow Delete' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1054, 'am', 'Regression Build' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1055, 'am', 'Classification Build' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1056, 'am', 'Build Text' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1057, 'am', 'Apply Text' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1058, 'am', 'Build Text Reference' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1059, 'am', 'Item Value' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1060, 'am', 'Project' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1061, 'am', 'Workflow Rename' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1062, 'am', 'workflow definition is invalid' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1063, 'am', 'Start' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1064, 'am', 'End' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1065, 'am', 'Workflow' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1066, 'am', 'Node' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1067, 'am', 'SubNode' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1068, 'am', 'Validate' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1069, 'am', 'Sample' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1070, 'am', 'Cache' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1071, 'am', 'Statistics' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1072, 'am', 'Features' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1073, 'am', 'Data Preparation' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1074, 'am', 'Build' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1075, 'am', 'Test' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1076, 'am', 'Apply' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1077, 'am', 'Transformation' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1078, 'am', 'Text' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1079, 'am', 'BuildText' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1080, 'am', 'ApplyText' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1081, 'am', 'Output' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1082, 'am', 'Clean Up' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1083, 'am', 'Dynamic Prediction' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1084, 'am', 'Dynamic Cluster' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1085, 'am', 'Dynamic Feature' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1086, 'am', 'Dynamic Anomaly' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1087, 'am', 'SQL Query' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1088, 'am', 'Graph' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1089, 'am', 'Invalid Node(s)' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1090, 'am', 'JSON data has structural change.' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1091, 'am', 'Unbounded' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1092, 'am', 'Null bin' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1093, 'am', 'Workflow Export' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1094, 'am', 'Other' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1095, 'am', 'Create Project' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1096, 'am', 'Delete Project' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1097, 'am', 'Rename Project' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1098, 'am', 'Set Comment' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1099, 'am', 'Create Workflow' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1100, 'am', 'Cancel Workflow' )
 INTO ODMRSYS.ODMR$MESSAGES(message_id,language_id,message) VALUES (1101, 'am', 'Workflow Import' )
SELECT * FROM DUAL;
COMMIT;
