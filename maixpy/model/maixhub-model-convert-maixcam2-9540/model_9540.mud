
[basic]
type = axmodel
model_npu = model_9540_npu.axmodel
model_vnpu = model_9540_vnpu.axmodel

[extra]
model_type = yolo26
type=detector
input_type = rgb

input_cache = true
output_cache = true
input_cache_flush = false
output_cache_inval = true

labels = orange, green, blue, black, zone1, zone2
mean = 0, 0, 0
scale = 0.00392156862745098, 0.00392156862745098, 0.00392156862745098

