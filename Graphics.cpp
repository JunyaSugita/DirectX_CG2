#include "Graphics.h"

Graphics::Graphics() {
}

Graphics::~Graphics() {
}

void Graphics::Process(IniDX* iniDX, Draw* draw) {
	// �o�b�N�o�b�t�@�̔ԍ����擾(2�Ȃ̂�0�Ԃ�1��)
	UINT bbIndex = iniDX->swapChain->GetCurrentBackBufferIndex();
	// 1.���\�[�X�o���A�ŏ������݉\�ɕύX
	D3D12_RESOURCE_BARRIER barrierDesc{};
	barrierDesc.Transition.pResource = iniDX->backBuffers[bbIndex]; // �o�b�N�o�b�t�@���w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT; // �\����Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`���Ԃ�
	iniDX->commandList->ResourceBarrier(1, &barrierDesc);
	// 2.�`���̕ύX
	// �����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = iniDX->rtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * iniDX->device->GetDescriptorHandleIncrementSize(iniDX->rtvHeapDesc.Type);
	iniDX->commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	// 3.��ʃN���A R G B A
	FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f }; // ���ۂ��F
	iniDX->commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	// 4.�`��R�}���h
	// �r���[�|�[�g�ݒ�R�}���h
	D3D12_VIEWPORT viewport{};
	viewport.Width = WIN_WIDTH;
	viewport.Height = WIN_HEIGHT;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	iniDX->commandList->RSSetViewports(1, &viewport);

	// �V�U�[��`
	D3D12_RECT scissorRect{};
	scissorRect.left = 0; // �؂蔲�����W��
	scissorRect.right = scissorRect.left + WIN_WIDTH; // �؂蔲�����W�E
	scissorRect.top = 0; // �؂蔲�����W��
	scissorRect.bottom = scissorRect.top + WIN_HEIGHT; // �؂蔲�����W��
	// �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	iniDX->commandList->RSSetScissorRects(1, &scissorRect);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	iniDX->commandList->SetPipelineState(draw->pipelineState);
	iniDX->commandList->SetGraphicsRootSignature(draw->rootSignature);

	// �v���~�e�B�u�`��̐ݒ�R�}���h///////////////////////////////////////////////////////
	iniDX->commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);// 
	//////////////////////////////////////////////////////////////////////////////////
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	iniDX->commandList->IASetVertexBuffers(0, 1, &draw->vbView);

	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	iniDX->commandList->SetGraphicsRootConstantBufferView(0, draw->constBuffMaterial->GetGPUVirtualAddress());
	//SRV�q�[�v�̐ݒ�R�}���h
	iniDX->commandList->SetDescriptorHeaps(1, &draw->srvHeap);
	//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = draw->srvHeap->GetGPUDescriptorHandleForHeapStart();
	//SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	iniDX->commandList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	iniDX->commandList->SetGraphicsRootConstantBufferView(2, draw->constBuffTransform->GetGPUVirtualAddress());

	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	iniDX->commandList->IASetIndexBuffer(&draw->ibView);

	// �`��R�}���h
	//iniDX->commandList->DrawInstanced(draw->vertices.size(), 1, 0, 0);
	iniDX->commandList->DrawIndexedInstanced(draw->indices.size(), 1, 0, 0, 0); // �S�Ă̒��_���g���ĕ`��

	// 5.���\�[�X�o���A��߂�
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`���Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT; // �\����Ԃ�
	iniDX->commandList->ResourceBarrier(1, &barrierDesc);

	// ���߂̃N���[�Y
	iniDX->result = iniDX->commandList->Close();
	assert(SUCCEEDED(iniDX->result));
	// �R�}���h���X�g�̎��s
	ID3D12CommandList* commandLists[] = { iniDX->commandList };
	iniDX->commandQueue->ExecuteCommandLists(1, commandLists);
	// ��ʂɕ\������o�b�t�@���t���b�v(���\�̓��ւ�)
	iniDX->result = iniDX->swapChain->Present(1, 0);
	assert(SUCCEEDED(iniDX->result));

	// �R�}���h�̎��s������҂�
	iniDX->commandQueue->Signal(iniDX->fence, ++iniDX->fenceVal);
	if (iniDX->fence->GetCompletedValue() != iniDX->fenceVal) {
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		iniDX->fence->SetEventOnCompletion(iniDX->fenceVal, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}
	// �L���[���N���A
	iniDX->result = iniDX->commandAllocator->Reset();
	assert(SUCCEEDED(iniDX->result));
	// �ĂуR�}���h���X�g�𒙂߂鏀��
	iniDX->result = iniDX->commandList->Reset(iniDX->commandAllocator, nullptr);
	assert(SUCCEEDED(iniDX->result));
}
