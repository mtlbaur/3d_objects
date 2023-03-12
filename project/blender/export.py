# https://docs.blender.org/api/current/bpy.ops.wm.html#bpy.ops.wm.obj_export

import bpy

path = "../../../dev/c++/projects/3d_objects/project/resources/"
ext = ".obj"
args = {
    "filepath": path + "DEFAULT" + ext,
    "apply_modifiers": False,
    "export_selected_objects": True,
    "export_uv": False,
    "export_normals": True,
    "export_colors": False,
    "export_materials": False,
    "export_pbr_extensions": False,
    "export_triangulated_mesh": True
}
ignored_types = (["CAMERA", "LIGHT"])
selected = []

for o in bpy.data.objects:
    selected.append(o.select_get())
    o.select_set(False)

for o in bpy.data.objects:
    if (o.type in ignored_types): continue

    o.select_set(True)

    args["filepath"] = path + o.name + ext
    bpy.ops.wm.obj_export(**args)

    o.select_set(False)

for o, s in zip(bpy.data.objects, selected):
    o.select_set(s)