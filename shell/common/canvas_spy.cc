// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/shell/common/canvas_spy.h"

namespace flutter {

CanvasSpy::CanvasSpy(SkCanvas* target_canvas) {
  SkISize canvas_size = target_canvas->getBaseLayerSize();
  n_way_canvas_ =
      std::make_unique<SkNWayCanvas>(canvas_size.width(), canvas_size.height());
  did_draw_canvas_ = std::make_unique<DidDrawCanvas>(canvas_size.width(),
                                                     canvas_size.height());
  n_way_canvas_->addCanvas(target_canvas);
  n_way_canvas_->addCanvas(did_draw_canvas_.get());
}

SkCanvas* CanvasSpy::GetSpyingCanvas() {
  return n_way_canvas_.get();
}

DidDrawCanvas::DidDrawCanvas(int width, int height)
    : SkCanvasVirtualEnforcer<SkNoDrawCanvas>(width, height) {}

DidDrawCanvas::~DidDrawCanvas() {}

void DidDrawCanvas::MarkDrawIfNonTransparentPaint(const SkPaint& paint) {
  bool isTransparent = paint.getAlpha() == 0;
  did_draw_ |= !isTransparent;
}

bool CanvasSpy::DidDrawIntoCanvas() {
  return did_draw_canvas_->DidDrawIntoCanvas();
}

bool DidDrawCanvas::DidDrawIntoCanvas() {
  return did_draw_;
}

void DidDrawCanvas::willSave() {}

SkCanvas::SaveLayerStrategy DidDrawCanvas::getSaveLayerStrategy(
    const SaveLayerRec& rec) {
  return kNoLayer_SaveLayerStrategy;
}

bool DidDrawCanvas::onDoSaveBehind(const SkRect* bounds) {
  return false;
}

void DidDrawCanvas::willRestore() {}

void DidDrawCanvas::didConcat(const SkMatrix& matrix) {}

void DidDrawCanvas::didSetMatrix(const SkMatrix& matrix) {}

void DidDrawCanvas::onClipRect(const SkRect& rect,
                               SkClipOp op,
                               ClipEdgeStyle edgeStyle) {}

void DidDrawCanvas::onClipRRect(const SkRRect& rrect,
                                SkClipOp op,
                                ClipEdgeStyle edgeStyle) {}

void DidDrawCanvas::onClipPath(const SkPath& path,
                               SkClipOp op,
                               ClipEdgeStyle edgeStyle) {}

void DidDrawCanvas::onClipRegion(const SkRegion& deviceRgn, SkClipOp op) {}

void DidDrawCanvas::onDrawPaint(const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawBehind(const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawPoints(PointMode mode,
                                 size_t count,
                                 const SkPoint pts[],
                                 const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawRect(const SkRect& rect, const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawRegion(const SkRegion& region, const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawOval(const SkRect& rect, const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawArc(const SkRect& rect,
                              SkScalar startAngle,
                              SkScalar sweepAngle,
                              bool useCenter,
                              const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawRRect(const SkRRect& rrect, const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawDRRect(const SkRRect& outer,
                                 const SkRRect& inner,
                                 const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawPath(const SkPath& path, const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawBitmap(const SkBitmap& bitmap,
                                 SkScalar x,
                                 SkScalar y,
                                 const SkPaint* paint) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawBitmapRect(const SkBitmap& bitmap,
                                     const SkRect* src,
                                     const SkRect& dst,
                                     const SkPaint* paint,
                                     SrcRectConstraint constraint) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawBitmapNine(const SkBitmap& bitmap,
                                     const SkIRect& center,
                                     const SkRect& dst,
                                     const SkPaint* paint) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawBitmapLattice(const SkBitmap& bitmap,
                                        const Lattice& lattice,
                                        const SkRect& dst,
                                        const SkPaint* paint) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawImage(const SkImage* image,
                                SkScalar left,
                                SkScalar top,
                                const SkPaint* paint) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawImageRect(const SkImage* image,
                                    const SkRect* src,
                                    const SkRect& dst,
                                    const SkPaint* paint,
                                    SrcRectConstraint constraint) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawImageNine(const SkImage* image,
                                    const SkIRect& center,
                                    const SkRect& dst,
                                    const SkPaint* paint) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawImageLattice(const SkImage* image,
                                       const Lattice& lattice,
                                       const SkRect& dst,
                                       const SkPaint* paint) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawTextBlob(const SkTextBlob* blob,
                                   SkScalar x,
                                   SkScalar y,
                                   const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawPicture(const SkPicture* picture,
                                  const SkMatrix* matrix,
                                  const SkPaint* paint) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawDrawable(SkDrawable* drawable,
                                   const SkMatrix* matrix) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawVerticesObject(const SkVertices* vertices,
                                         const SkVertices::Bone bones[],
                                         int boneCount,
                                         SkBlendMode bmode,
                                         const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawPatch(const SkPoint cubics[12],
                                const SkColor colors[4],
                                const SkPoint texCoords[4],
                                SkBlendMode bmode,
                                const SkPaint& paint) {
  MarkDrawIfNonTransparentPaint(paint);
}

void DidDrawCanvas::onDrawAtlas(const SkImage* image,
                                const SkRSXform xform[],
                                const SkRect tex[],
                                const SkColor colors[],
                                int count,
                                SkBlendMode bmode,
                                const SkRect* cull,
                                const SkPaint* paint) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawShadowRec(const SkPath& path,
                                    const SkDrawShadowRec& rec) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawAnnotation(const SkRect& rect,
                                     const char key[],
                                     SkData* data) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawEdgeAAQuad(const SkRect& rect,
                                     const SkPoint clip[4],
                                     QuadAAFlags aa,
                                     SkColor color,
                                     SkBlendMode mode) {
  did_draw_ = true;
}

void DidDrawCanvas::onDrawEdgeAAImageSet(const ImageSetEntry set[],
                                         int count,
                                         const SkPoint dstClips[],
                                         const SkMatrix preViewMatrices[],
                                         const SkPaint* paint,
                                         SrcRectConstraint constraint) {
  did_draw_ = true;
}

void DidDrawCanvas::onFlush() {}

}  // namespace flutter
