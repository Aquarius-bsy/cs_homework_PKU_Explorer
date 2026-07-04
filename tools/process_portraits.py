"""Process dialogue portraits: remove backdrop, crop to half-body, warm tint, shadow."""

from __future__ import annotations

import argparse
import shutil
from collections import deque
from pathlib import Path

from PIL import Image, ImageFilter

ROOT = Path(__file__).resolve().parents[1]
IMAGES = ROOT / "images"
BACKUP = IMAGES / "_original_portraits"

TAVERN_PORTRAIT_CONFIG = {
    "witch.png": {"warm": 0.05, "upper_ratio": 0.62, "target_height": 920},
    "bar_publican.png": {"warm": 0.11, "upper_ratio": 0.65, "target_height": 920},
    "bar_stranger.png": {"warm": 0.11, "upper_ratio": 0.56, "target_height": 920},
}

ABATTOIR_PORTRAIT_CONFIG = {
    "abattoir_warrior.png": {"warm": 0.10, "upper_ratio": 0.60, "target_height": 920},
    "abattoir_manager.png": {"warm": 0.10, "upper_ratio": 0.68, "target_height": 920},
    "abattoir_audience_1.png": {"warm": 0.09, "upper_ratio": 0.54, "target_height": 880},
    "abattoir_audience_2.png": {"warm": 0.09, "upper_ratio": 0.54, "target_height": 880},
}

SITE_STAFF_PORTRAIT_CONFIG = {
    "theater_staff.png": {"warm": 0.08, "upper_ratio": 1.0, "target_height": 920},
    "library_assistance.png": {"warm": 0.08, "upper_ratio": 1.0, "target_height": 920},
}

THEATER_PORTRAIT_CONFIG = SITE_STAFF_PORTRAIT_CONFIG

PORTRAIT_CONFIG = {**TAVERN_PORTRAIT_CONFIG, **ABATTOIR_PORTRAIT_CONFIG, **THEATER_PORTRAIT_CONFIG}


def ensure_backup(name: str) -> Path:
    BACKUP.mkdir(parents=True, exist_ok=True)
    backup_path = BACKUP / name
    live_path = IMAGES / name
    if not backup_path.exists():
        if not live_path.exists():
            raise FileNotFoundError(f"Missing portrait: {live_path}")
        shutil.copy2(live_path, backup_path)
    return backup_path


def resolve_portrait_source(name: str) -> Path:
    """Pick the source PNG to process. Never overwrite a newer live file with backup."""
    live_path = IMAGES / name
    backup_path = BACKUP / name

    if not live_path.exists():
        if not backup_path.exists():
            raise FileNotFoundError(f"Missing portrait: {live_path}")
        return backup_path

    if not backup_path.exists():
        shutil.copy2(live_path, backup_path)
        return live_path

    live_mtime = live_path.stat().st_mtime
    backup_mtime = backup_path.stat().st_mtime
    if live_mtime >= backup_mtime:
        shutil.copy2(live_path, backup_path)
        return live_path

    return backup_path


def restore_from_backup(name: str) -> Path:
    """Restore live portrait from backup only when explicitly requested."""
    src = ensure_backup(name)
    dst = IMAGES / name
    shutil.copy2(src, dst)
    return dst


def remove_checkerboard(img: Image.Image) -> Image.Image:
    rgba = img.convert("RGBA")
    pixels = rgba.load()
    width, height = rgba.size

    for y in range(height):
        for x in range(width):
            r, g, b, a = pixels[x, y]
            if abs(int(r) - int(g)) <= 12 and abs(int(g) - int(b)) <= 12 and 140 <= r <= 255:
                pixels[x, y] = (r, g, b, 0)
    return rgba


def is_light_backdrop_pixel(r: int, g: int, b: int, a: int) -> bool:
    """Only treat obvious light-gray / white matting pixels as backdrop."""
    if a < 8:
        return True
    return abs(int(r) - int(g)) <= 12 and abs(int(g) - int(b)) <= 12 and 140 <= r <= 255


def remove_light_backdrop(img: Image.Image) -> Image.Image:
    """Flood-fill light backdrop from image edges only.

    Avoids treating dark clothing, shadows, hair, or magic effects as background.
    """
    rgba = img.convert("RGBA")
    pixels = rgba.load()
    width, height = rgba.size

    seeds: list[tuple[int, int]] = []
    for x in range(width):
        seeds.append((x, 0))
        seeds.append((x, height - 1))
    for y in range(height):
        seeds.append((0, y))
        seeds.append((width - 1, y))

    visited: set[tuple[int, int]] = set()
    queue: deque[tuple[int, int]] = deque()

    for point in seeds:
        if point not in visited:
            visited.add(point)
            queue.append(point)

    while queue:
        x, y = queue.popleft()
        r, g, b, a = pixels[x, y]
        if not is_light_backdrop_pixel(r, g, b, a):
            continue
        pixels[x, y] = (r, g, b, 0)
        for nx, ny in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)):
            if 0 <= nx < width and 0 <= ny < height and (nx, ny) not in visited:
                visited.add((nx, ny))
                queue.append((nx, ny))

    return rgba


def trim_transparent(img: Image.Image, padding: int = 8) -> Image.Image:
    alpha = img.split()[3]
    bbox = alpha.getbbox()
    if not bbox:
        return img
    left, top, right, bottom = bbox
    left = max(0, left - padding)
    top = max(0, top - padding)
    right = min(img.width, right + padding)
    bottom = min(img.height, bottom + padding)
    return img.crop((left, top, right, bottom))


def crop_upper_body(img: Image.Image, keep_ratio: float) -> Image.Image:
    rgba = trim_transparent(img, padding=0)
    alpha = rgba.split()[3]
    bbox = alpha.getbbox()
    if not bbox:
        return rgba

    left, top, right, bottom = bbox
    body_height = bottom - top
    cut = top + max(1, int(body_height * keep_ratio))
    return rgba.crop((left, top, right, cut))


def soften_edges(img: Image.Image, radius: float = 0.9) -> Image.Image:
    rgba = img.convert("RGBA")
    r, g, b, a = rgba.split()
    a = a.filter(ImageFilter.GaussianBlur(radius))
    return Image.merge("RGBA", (r, g, b, a))


def warm_tint(img: Image.Image, strength: float) -> Image.Image:
    rgba = img.convert("RGBA")
    warm = Image.new("RGBA", rgba.size, (255, 200, 130, int(255 * strength)))
    out = Image.alpha_composite(rgba, warm)
    out.putalpha(rgba.split()[3])
    return out


def add_ground_shadow(img: Image.Image) -> Image.Image:
    rgba = img.convert("RGBA")
    w, h = rgba.size
    canvas = Image.new("RGBA", (w, h + 18), (0, 0, 0, 0))

    alpha = rgba.split()[3]
    shadow = Image.new("RGBA", rgba.size, (0, 0, 0, 0))
    shadow.putalpha(alpha)
    shadow = shadow.filter(ImageFilter.GaussianBlur(12))

    shadow_layer = Image.new("RGBA", canvas.size, (0, 0, 0, 0))
    shadow_layer.paste(shadow, (10, h - 1), shadow)
    shadow_pixels = shadow_layer.load()
    sw, sh = shadow_layer.size
    for y in range(sh):
        for x in range(sw):
            _, _, _, a = shadow_pixels[x, y]
            if a:
                shadow_pixels[x, y] = (0, 0, 0, min(95, int(a * 0.40)))

    canvas.alpha_composite(shadow_layer)
    canvas.alpha_composite(rgba, (0, 0))
    return canvas


def scale_to_height(img: Image.Image, target_height: int) -> Image.Image:
    w, h = img.size
    if h == target_height:
        return img
    scale = target_height / h
    new_w = max(1, int(w * scale))
    return img.resize((new_w, target_height), Image.Resampling.LANCZOS)


def process_portrait(name: str, config: dict[str, dict] | None = None) -> None:
    cfg = (config or PORTRAIT_CONFIG)[name]
    path = resolve_portrait_source(name)
    img = Image.open(path).convert("RGBA")

    img = remove_checkerboard(img)
    img = remove_light_backdrop(img)
    img = crop_upper_body(img, cfg["upper_ratio"])
    img = trim_transparent(img, 10)
    img = scale_to_height(img, cfg["target_height"])
    img = trim_transparent(img, 4)
    img = soften_edges(img, 1.0)
    img = warm_tint(img, cfg["warm"])
    if not cfg.get("skip_shadow"):
        img = add_ground_shadow(img)
    img.save(path)
    print(f"Updated {name} -> {img.size[0]}x{img.size[1]}", flush=True)


def main() -> None:
    parser = argparse.ArgumentParser(description="Process dialogue portrait PNGs.")
    parser.add_argument(
        "--set",
        choices=("all", "tavern", "abattoir", "theater"),
        default="all",
        help="Which portrait set to process (default: all).",
    )
    parser.add_argument(
        "--restore",
        action="store_true",
        help="Restore live PNGs from _original_portraits before processing.",
    )
    parser.add_argument(
        "--restore-only",
        action="store_true",
        help="Restore live PNGs from backup without reprocessing.",
    )
    args = parser.parse_args()

    if args.set == "tavern":
        config = TAVERN_PORTRAIT_CONFIG
    elif args.set == "abattoir":
        config = ABATTOIR_PORTRAIT_CONFIG
    elif args.set == "theater":
        config = THEATER_PORTRAIT_CONFIG
    else:
        config = PORTRAIT_CONFIG

    for name in config:
        if args.restore or args.restore_only:
            restore_from_backup(name)
            print(f"Restored {name}", flush=True)
        if args.restore_only:
            continue
        process_portrait(name, config)
    print("Done.", flush=True)


if __name__ == "__main__":
    main()
