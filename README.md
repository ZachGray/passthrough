# Passthrough node
An attempt to replicate cycle check errors on compound attribures

```python
import maya.cmds as mc
passthrough_node = mc.createNode('passthrough')
color_in_node = mc.createNode('colorConstant')
color_out_node = mc.createNode('colorConstant')

mc.connectAttr(f'{color_in_node}.outColor', f'{passthrough_node}.palette[0].color0', force=True)
mc.connectAttr(f'{passthrough_node}.palette[0].color0', f'{color_out_node}.inColor', force=True)
mc.select(passthrough_node)
```
