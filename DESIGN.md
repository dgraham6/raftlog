lld Design Doc
to be written somewhat concurrently for my sanity 

1 Executive Summary


2 Background

3 Requirements

4 Design 

4.1 Data Flow Sequence Digrams

4.2 Architecture

4.3 Design Decisions 

encode decode 
Use crc for cheksum
correct tradeoff on collision and scale 

Write files to temp_directory path, cleanup should be some time of RAII down the line
